#include <cart.h>
#include <string.h>

#define NUM_RAM_TYPES 5

typedef enum {
    EEPROM_V = 0x02000,     // 8KB
    SRAM_V = 0x08000,       // 32KB
    FLASH_V = 0x10000,      // 64KB
    FLASH512_V = 0x10000,   // 64KB
    FLASH1M_V = 0x20000,    // 128KB
} ram_type;

typedef struct {
    // ROM Data
    char filename[1024];
    uint32_t rom_size;
    uint8_t *rom_data;
    rom_header *header;

    // RAM Data
    ram_type ram_type;
    uint8_t *ram_data;
} cart_context;

static cart_context ctx;

static char *cart_ram_types_lookup[] = {
    "EEPROM_V",
    "SRAM_V",
    "FLASH_V",
    "FLASH512_V",
    "FLASH1M_V",
};


static uint8_t checksum() {
    uint16_t checksum = 0;
    for (int i = 0x0A0; i < 0x0BC; i++) {
        checksum = checksum - ctx.rom_data[i];
    }
    return ((checksum - 0x19) & 0xFF);
}

static void find_ram_type() {
    for(int word = 0; word < ctx.rom_size - 10; word+=4) {
        for(int type = 0; type < NUM_RAM_TYPES; type++) {
            if(memcmp(&ctx.rom_data[word], cart_ram_types_lookup[type], strlen(cart_ram_types_lookup[type]) - 1) == 0) {
                switch (type) {
                    case 0:
                        ctx.ram_type = EEPROM_V;
                        break;
                    case 1:
                        ctx.ram_type = SRAM_V;
                        break;
                    case 2:
                        ctx.ram_type = FLASH_V;
                        break;
                    case 3:
                        ctx.ram_type = FLASH512_V;
                        break;
                    case 4:
                        ctx.ram_type = FLASH1M_V;
                        break;
                }
                return;
            }
        }
    }
}

static void init_ram() {
    ctx.ram_data = malloc(ctx.ram_type);
    if (!ctx.ram_data) {
        printf("Failed to allocate RAM...\n");
        exit(1);
    }
    memset(ctx.ram_data, 0, ctx.ram_type);
}

/**
 * @brief Loads a cart into the context.
 * 
 * @param cart the filename of the cart to load.
 * @return true if the cart is loaded successfully.
 * @return false if the cart failed to load.
 */
bool cart_load(char *cart) {
    snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

    FILE *fp = fopen(cart, "r");
    if (!fp) {
        printf("Failed to open ROM...\n");
        return false;
    }

    printf("Opened: %s\n", ctx.filename);

    fseek(fp, 0, SEEK_END);
    ctx.rom_size = ftell(fp);
    rewind(fp);

    ctx.rom_data = malloc(ctx.rom_size);
    fread(ctx.rom_data, ctx.rom_size, 1, fp);
    fclose(fp);

    ctx.header = (rom_header *)(ctx.rom_data);
    printf("Checksum: %s\n", checksum() == ctx.header->checksum ? "OK" : "BAD");

    find_ram_type();

    init_ram();

    return true;
}

/**
 * @brief Loads the game state from a .sav file into cart ram.
 * 
 */
void cart_load_ram() {
    char filename[1048];
    snprintf(filename, sizeof(filename), "%s.sav", ctx.filename);
    FILE *fp = fopen(filename, "rb");

    if (!fp) {
        printf("Failed to open save...\n");
        return;
    }

    fread(ctx.ram_data, ctx.ram_type, 1, fp);
    fclose(fp);
}

/**
 * @brief Saves the game state from cart ram into a .sav file.
 * 
 */
void cart_save_ram() {
    char filename[1048];
    snprintf(filename, sizeof(filename), "%s.sav", ctx.filename);
    FILE *fp = fopen(filename, "wb");

    if (!fp) {
        printf("Failed to open save...\n");
        return;
    }

    fwrite(ctx.ram_data, ctx.ram_type, 1, fp);
    fclose(fp);
}

/**
 * @brief Writes a byte to the cart ram.
 * 
 * @param addr the address to write to.
 * @param val the value to write.
 */
void write_cart_ram(uint32_t addr, uint8_t val) {
    if (addr >> 27 == 0x01) {
        addr -= 0x08000000;
        if (addr < 0x00 || addr >= ctx.ram_type) {
            printf("INVALID RAM ADDR %08X\n", addr + 0x0A000000);
            exit(-1);
        }
        ctx.ram_data[addr] = val;
    }
}


/**
 * @brief Reads a byte from the cart ram.
 * 
 * @param addr the address to read from.
 * @return uint8_t the value at the address.
 */
uint8_t read_cart_ram(uint32_t addr) {
    if (addr >> 27 == 0x01) {
        addr -= 0x08000000;
        if (addr < 0x00 || addr >= ctx.ram_type) {
            printf("INVALID RAM ADDR %08X\n", addr + 0x0A000000);
            exit(-1);
        }
        return ctx.ram_data[addr];
    } else {
        printf("NOT CART RAM ADDRESS %08X\n", addr);
        exit(-1);
    }
}

/**
 * @brief Writes a 16-bit value to the cart ram.
 * 
 * @param addr the address to write to.
 * @param val the value to write.
 */
void write_cart_ram16(uint32_t addr, uint16_t val) {
    write_cart_ram(addr, val & 0xFF);
    write_cart_ram(addr + 1, val >> 8);
}

/**
 * @brief Reads a 16-bit value from the cart ram.
 * 
 * @param addr the address to read from.
 * @return uint16_t the value at the address.
 */
uint16_t read_cart_ram16(uint32_t addr) {
    return (read_cart_ram(addr) | (read_cart_ram(addr + 1) << 8));
}
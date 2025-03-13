#include <cart.h>
#include <string.h>

typedef struct {
    // ROM Data
    char filename[1024];
    uint32_t rom_size;
    uint8_t *rom_data;
    rom_header *header;

    // RAM Data
    uint8_t ram_type;
    uint8_t *ram_data;
} cart_context;

static cart_context ctx;

static const char *cart_ram_types[] = {
    "EEPROM_V",     // 0x00
    "SRAM_V",       // 0x01
    "FLASH_V",      // 0x02
    "FLASH512_V",   // 0x03
    "FLASH1M_V",    // 0x04
};

static const size_t num_cart_ram_types = sizeof(cart_ram_types) / sizeof(cart_ram_types[0]);

/**
 * @brief A simple checksum function that checks the ROM data.
 * 
 * @return uint8_t the checksum value.
 */
static uint8_t checksum() {
    uint16_t checksum = 0;
    for (int i = 0x0A0; i < 0x0BC; i++) {
        checksum = checksum - ctx.rom_data[i];
    }
    return ((checksum - 0x19) & 0xFF);
}

/**
 * @brief Sets the ram type for the cart context.
 */
static void find_ram_type() {
    for(int word = 0; word < ctx.rom_size - 10; word+=4) {
        for(int type = 0; type < num_cart_ram_types; type++) {
            if(memcmp(&ctx.rom_data[word], cart_ram_types[type], strlen(cart_ram_types[type]) - 1) == 0) {
                ctx.ram_type = type;
                return;
            }
        }
    }
}

static void init_ram() {
    switch(ctx.ram_type) {
        case 0x00: // EEPROM_Vnnn
            ctx.ram_data = malloc(0x2000);
            break;
        case 0x01: // SRAM_Vnnn
            ctx.ram_data = malloc(0x8000);
            break;
        case 0x02: // FLASH_Vnnn
            ctx.ram_data = malloc(0x10000);
            break;
        case 0x03: // FLASH512_Vnnn
            ctx.ram_data = malloc(0x10000);
            break;
        case 0x04: // FLASH1M_Vnnn
            ctx.ram_data = malloc(0x20000);
            break;
        default: // No RAM
            ctx.ram_data = NULL;
            break;
    }
    if (!ctx.ram_data) {
        printf("Failed to allocate RAM...\n");
        exit(1);
    }
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
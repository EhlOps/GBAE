#include <cart.h>
#include <string.h>

#define NUM_RAM_TYPES 5

typedef enum {
  EEPROM_V = 0x02000,   // 8KB
  SRAM_V = 0x08000,     // 32KB
  FLASH_V = 0x10000,    // 64KB
  FLASH512_V = 0x10000, // 64KB
  FLASH1M_V = 0x20000,  // 128KB
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
    "EEPROM_V", "SRAM_V", "FLASH_V", "FLASH512_V", "FLASH1M_V",
};

static uint8_t checksum() {
  uint16_t checksum = 0;
  for (int i = 0x0A0; i < 0x0BC; i++) {
    checksum = checksum - ctx.rom_data[i];
  }
  return ((checksum - 0x19) & 0xFF);
}

static void find_ram_type() {
  for (int word = 0; word < ctx.rom_size - 10; word += 4) {
    for (int type = 0; type < NUM_RAM_TYPES; type++) {
      if (memcmp(&ctx.rom_data[word], cart_ram_types_lookup[type],
                 strlen(cart_ram_types_lookup[type]) - 1) == 0) {
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
  memset(ctx.ram_data, 0, ctx.ram_type);
}

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

uint8_t cart_read_ram8(uint32_t addr) {
  if (addr >> 24 == 0x0E) {
    addr -= CART_RAM_START;
    if (addr < 0x00 || addr >= ctx.ram_type) {
      fprintf(stderr, "INVALID RAM ADDR 0x%08X\n", addr + 0x0A000000);
      exit(EXIT_FAILURE);
    }
    return ctx.ram_data[addr];
  } else {
    fprintf(stderr, "NOT CART RAM ADDRESS 0x%08X\n", addr);
    exit(EXIT_FAILURE);
  }
}

void cart_write_ram8(uint32_t addr, uint8_t val) {
  if (addr >> 24 == 0x0E) {
    addr -= CART_RAM_START;
    if (addr < 0x00 || addr >= ctx.ram_type) {
      fprintf(stderr, "INVALID RAM ADDR 0x%08X\n", addr + 0x0A000000);
      exit(EXIT_FAILURE);
    }

    ctx.ram_data[addr] = val;
  }
}

void cart_write_rom8(uint32_t addr, uint8_t val){NO_IMPL}

uint8_t cart_read_rom8(uint32_t addr) {
  if (addr >> 24 == 0x08) {
    addr -= CART_ROM_START;
    if (addr < 0x00 || addr >= ctx.rom_size) {
      fprintf(stderr, "INVALID ROM ADDR 0x%08X\n", addr + 0x08000000);
      exit(EXIT_FAILURE);
    }
    return ctx.rom_data[addr];
  } else {
    fprintf(stderr, "NOT CART ROM ADDRESS 0x%08X\n", addr);
    exit(EXIT_FAILURE);
  }
}
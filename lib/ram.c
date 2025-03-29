#include <ram.h>

static ram_context ctx;


uint8_t read_ewram8(uint32_t addr) {
  addr -= WRAM_START;

  if (addr < 0x00 || addr >= WRAM_SIZE) {
    printf("INVALID WRAM ADDR %08X\n", addr + 0x02000000);
    exit(-1);
  }

  return ctx.wram[addr];
}

void write_ewram8(uint32_t addr, uint16_t val) {
  addr -= WRAM_START;

  if (addr < 0x00 || addr >= WRAM_SIZE) {
    printf("INVALID WRAM ADDR %08X\n", addr + 0x02000000);
    exit(-1);
  }

  ctx.wram[addr] = val;
}

uint8_t read_iwram8(uint32_t addr) {
  addr -= HRAM_START;

  if (addr < 0x00 || addr >= HRAM_SIZE) {
    printf("INVALID HRAM ADDR %08X\n", addr + 0x03000000);
    exit(-1);
  }

  return ctx.hram[addr];
}

void write_iwram8(uint32_t addr, uint16_t val) {
  addr -= HRAM_START;

  if (addr < 0x00 || addr >= HRAM_SIZE) {
    printf("INVALID HRAM ADDR %08X\n", addr + 0x03000000);
    exit(-1);
  }

  ctx.hram[addr] = val;
}
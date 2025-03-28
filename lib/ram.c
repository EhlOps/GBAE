#include <ram.h>

static ram_context ctx;

/**
 * @brief Reads the two bytes at the given address in WRAM.
 *
 * @param addr The address to read from.
 * @return uint16_t The two bytes at the address.
 */
uint16_t read_wram(uint32_t addr) {
  addr -= WRAM_START;

  if (addr < 0x00 || addr >= WRAM_SIZE) {
    printf("INVALID WRAM ADDR %08X\n", addr + 0x02000000);
    exit(-1);
  }

  return ctx.wram[addr];
}

/**
 * @brief Writes two bytes to WRAM.
 *
 * @param addr The address to write to.
 * @param val The value to write.
 */
void write_wram(uint32_t addr, uint16_t val) {
  addr -= WRAM_START;

  if (addr < 0x00 || addr >= WRAM_SIZE) {
    printf("INVALID WRAM ADDR %08X\n", addr + 0x02000000);
    exit(-1);
  }

  ctx.wram[addr] = val;
}

/**
 * @brief Reads the four bytes at the given address in HRAM.
 *
 * @param addr The address to read from.
 * @return uint32_t The four bytes at the address.
 */
uint32_t read_hram(uint32_t addr) {
  addr -= HRAM_START;

  if (addr < 0x00 || addr >= HRAM_SIZE) {
    printf("INVALID HRAM ADDR %08X\n", addr + 0x03000000);
    exit(-1);
  }

  return ctx.hram[addr];
}

/**
 * @brief Writes four bytes to HRAM.
 *
 * @param addr The address to write to.
 * @param val The value to write.
 */
void write_hram(uint32_t addr, uint16_t val) {
  addr -= HRAM_START;

  if (addr < 0x00 || addr >= HRAM_SIZE) {
    printf("INVALID HRAM ADDR %08X\n", addr + 0x03000000);
    exit(-1);
  }

  ctx.hram[addr] = val;
}
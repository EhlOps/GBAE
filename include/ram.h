#pragma once

#include <common.h>

#define WRAM_START 0x02000000
#define WRAM_SIZE 0x0040000
#define HRAM_START 0x03000000
#define HRAM_SIZE 0x0008000

typedef struct {
  // 256KB of WRAM
  uint16_t wram[WRAM_SIZE];
  // 32KB of WRAM
  uint32_t hram[HRAM_SIZE];
} ram_context;

// LO-WRAM: 0x02000000 - 0x0203FFFF

/**
 * @brief Reads the two bytes at the given address in WRAM.
 *
 * @param addr The address to read from.
 * @return uint16_t The two bytes at the address.
 */
uint16_t read_wram16(uint32_t addr);

/**
 * @brief Writes two bytes to WRAM.
 *
 * @param addr The address to write to.
 * @param val The value to write.
 */
void write_wram16(uint32_t addr, uint16_t val);

// HI-WRAM: 0x03000000 - 0x03007FFF

/**
 * @brief Reads the four bytes at the given address in HRAM.
 *
 * @param addr The address to read from.
 * @return uint32_t The four bytes at the address.
 */
uint32_t read_hram16(uint32_t addr);

/**
 * @brief Writes four bytes to HRAM.
 *
 * @param addr The address to write to.
 * @param val The value to write.
 */
void write_hram(uint32_t addr, uint16_t val);
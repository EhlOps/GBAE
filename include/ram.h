#pragma once

#include <common.h>

#define WRAM_START 0x02000000
#define WRAM_SIZE 0x0040000
#define HRAM_START 0x03000000
#define HRAM_SIZE 0x0008000

typedef struct {
  // 256KB of WRAM
  uint8_t wram[WRAM_SIZE];
  // 32KB of WRAM
  uint8_t hram[HRAM_SIZE];
} ram_context;

// LO-WRAM: 0x02000000 - 0x0203FFFF

/**
 * @brief Reads the two bytes at the given address in External Working RAM.
 *
 * @param addr The address to read from.
 * @return uint16_t The two bytes at the address.
 */
uint8_t read_ewram8(uint32_t addr);

/**
 * @brief Writes two bytes to External Working RAM.
 *
 * @param addr The address to write to.
 * @param val The value to write.
 */
void write_ewram8(uint32_t addr, uint16_t val);

// HI-WRAM: 0x03000000 - 0x03007FFF

/**
 * @brief Reads the four bytes at the given address in Internal Working RAM.
 *
 * @param addr The address to read from.
 * @return uint32_t The four bytes at the address.
 */
uint8_t read_iwram8(uint32_t addr);

/**
 * @brief Writes four bytes to Internal Working RAM.
 *
 * @param addr The address to write to.
 * @param val The value to write.
 */
void write_iwram8(uint32_t addr, uint16_t val);
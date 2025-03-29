#pragma once

#include <common.h>

/**
 * @brief Read 8-bit value from bus
 *
 * @param addr bus address
 * @return value at that bus address
 */
uint8_t bus_read8(uint32_t addr);

/**
 * @brief Write 8-bit value to bus
 *
 * @param addr bus address
 * @param val value to write
 */
void bus_write8(uint32_t addr, uint8_t val);

/**
 * @brief Read 16-bit value from bus
 *
 * @param addr bus address
 *  @return value at that bus address
 */
uint16_t bus_read16(uint32_t addr);

/**
 * @brief Write 16-bit value to bus
 *
 * @param addr bus address
 * @param val value to write
 */
void bus_write16(uint32_t addr, uint16_t val);

/**
 * @brief Read 32-bit value from bus
 *
 * @param addr bus address
 * @return value at that bus address
 */
uint32_t bus_read32(uint32_t addr);

/**
 * @brief Write 32-bit value to bus
 *
 * @param addr bus address
 * @param val value to write
 */
void bus_write32(uint32_t addr, uint32_t val);
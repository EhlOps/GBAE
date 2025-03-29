#pragma once

#include <common.h>

/**
 * @brief Read 8-bit value from IO register
 *
 * @param addr IO address
 * @return value at that IO address
 */
uint8_t read_io8(uint32_t addr);

/**
 * @brief Write 8-bit value to IO register
 *
 * @param addr IO address
 * @param val value to write
 */
void write_io8(uint32_t addr, uint8_t val);
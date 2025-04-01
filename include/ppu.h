#pragma once

#include <common.h>

/**
 * @brief Fetch a value from the OAM.
 *
 * @param addr the address to fetch data at
 * @return uint8_t the value at the address
 */
uint8_t ppu_read_oam8(uint32_t addr);

/**
 * @brief Write a value to the OAM.
 *
 * @param addr the address to write the data to
 * @param val the value to write
 */
void ppu_write_oam8(uint32_t addr, uint8_t val);

/**
 * @brief Fetch a value from the VRAM.
 *
 * @param addr the address to fetch data at
 * @return uint8_t the value at the address
 */
uint8_t ppu_read_vram8(uint32_t addr);

/**
 * @brief Write a value to the VRAM.
 *
 * @param addr the address to write the data to
 * @param val the value to write
 */
void ppu_write_vram8(uint32_t addr, uint8_t val);

/**
 * @brief Write a value to the BG/OBJ RAM.
 *
 * @param addr the address to fetch data at
 * @return uint8_t the value at the address
 */
uint8_t ppu_read_bgobjram8(uint32_t addr);

/**
 * @brief Read a value from the BG/OBJ RAM.
 *
 * @param addr the address to write the data to
 * @param val the value to write
 */
void ppu_write_bgobjram8(uint32_t addr, uint8_t val);
#pragma once

#include <common.h>

/**
 * @brief 
 * 
 * @param addr 
 * @return uint8_t 
 */
uint8_t ppu_read_oam(uint32_t addr);

/**
 * @brief 
 * 
 * @param addr 
 * @param val 
 */
void ppu_write_oam(uint32_t addr, uint8_t val);
#pragma once

#include <common.h>

uint8_t bus_read8(uint16_t addr);
void bus_write8(uint16_t addr, uint8_t val);

uint16_t bus_read16(uint16_t addr);
void bus_write16(uint16_t addr, uint16_t val);

uint32_t bus_read32(uint16_t addr);
void bus_write32(uint16_t addr, uint32_t val);
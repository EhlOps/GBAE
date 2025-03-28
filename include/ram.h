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
uint16_t read_wram(uint32_t addr);
void write_wram(uint32_t addr, uint16_t val);

// HI-WRAM: 0x03000000 - 0x03007FFF
uint32_t read_hram(uint32_t addr);
void write_hram(uint32_t addr, uint16_t val);
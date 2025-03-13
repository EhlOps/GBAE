#pragma once
#include <common.h>

typedef struct {
    uint8_t rom_entry[4];
    uint8_t logo[0x9C];
    char title[12];
    char game_code[4];
    char maker_code[2];
    uint8_t fixed;
    uint8_t main_unit_code;
    uint8_t device_type;
    uint8_t reserved[7];
    uint8_t version;
    uint8_t checksum;
} rom_header;

// Cart save/load functions
bool cart_load(char *cart);
void cart_load_ram();
void cart_save_ram();

// Cart RAM functions
void write_cart_ram(uint32_t addr, uint8_t val);
uint8_t read_cart_ram(uint32_t addr);
void write_cart_ram16(uint32_t addr, uint16_t val);
uint16_t read_cart_ram16(uint32_t addr);
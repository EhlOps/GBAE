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

bool cart_load(char *cart);
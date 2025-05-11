#pragma once
#include <common.h>

#define CART_ROM_START 0x08000000
#define CART_RAM_START 0x0E000000

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

/**
 * @brief Loads a cart into the context.
 *
 * @param cart the filename of the cart to load.
 * @return true if the cart is loaded successfully.
 * @return false if the cart failed to load.
 */
bool cart_load(char *cart);

/**
 * @brief Loads the game state from a .sav file into cart ram.
 *
 */
void cart_load_ram();

/**
 * @brief Saves the game state from cart ram into a .sav file.
 *
 */
void cart_save_ram();

// Cart RAM functions

/**
 * @brief Reads a byte from the cart ram.
 *
 * @param addr the address to read from.
 * @return uint8_t the value at the address.
 */
void cart_write_ram8(uint32_t addr, uint8_t val);

/**
 * @brief Writes a byte to the cart ram.
 *
 * @param addr the address to write to.
 * @param val the value to write.
 */
uint8_t cart_read_ram8(uint32_t addr);

// Cart ROM functions

/**
 * @brief Writes a byte to the cart rom.
 *
 * @param addr the address to write to.
 * @param val the value to write.
 */
void cart_write_rom8(uint32_t addr, uint8_t val);

/**
 * @brief Reads a byte from the cart rom.
 *
 * @param addr the address to read from.
 * @return uint8_t the value at the address.
 */
uint8_t cart_read_rom8(uint32_t addr);
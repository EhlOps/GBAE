#include <bus.h>
#include <cart.h>
#include <io.h>
#include <ppu.h>
#include <ram.h>

//  Memory Map
//      Address Range            Description        Size    Bus Width
// ------------------------------------------------------------------
//  General Internal Memeory
//      0x00000000 - 0x00003FFF: BIOS               (16KB)  32-bit
//      0x00004000 - 0x 01FFFFF: Not Used
//      0x02000000 - 0x0203FFFF: WRAM               (256KB) 16-bit
//      0x02040000 - 0x02FFFFFF: Not Used
//      0x03000000 - 0x03007FFF: WRAM               (32KB)  32-bit
//      0x03008000 - 0x03FFFFFF: Not Used
//      0x04000000 - 0x040003FE: IO Registers       (512B)  32-bit
//      0x04000400 - 0x04FFFFFF: Not Used
// ------------------------------------------------------------------
//  Internal Display Memory
//      0x05000000 - 0x050003FF: BG/OBJ Palette RAM (1KB)   16-bit
//      0x05000400 - 0x05FFFFFF: Not Used
//      0x06000000 - 0x06017FFF: VRAM               (96KB)  16-bit
//      0x06018000 - 0x06FFFFFF: Not Used
//      0x07000000 - 0x070003FF: OAM                (1KB)   32-bit
//      0x07000400 - 0x07FFFFFF: Not Used
// ------------------------------------------------------------------
//  External Memory (Game Pak)
//      0x08000000 - 0x09FFFFFF: ROM - Wait State 0 (32MB)  16-bit
//      0x0A000000 - 0x0BFFFFFF: ROM - Wait State 1 (32MB)  16-bit
//      0x0C000000 - 0x0DFFFFFF: ROM - Wait State 2 (32MB)  16-bit
//      0x0E000000 - 0x0E00FFFF: Game Pak SRAM      (64KB)  8-bit

// TODO: Fix rams and bus to actually store the correct types

uint16_t bus_read16(uint32_t addr) {
  return bus_read8(addr) | (bus_read8(addr + 1) << 8);
}

uint32_t bus_read32(uint32_t addr) {
  return bus_read16(addr) | (bus_read16(addr + 2) << 16);
}

uint8_t bus_read8(uint32_t addr) {
  // WRAM (256KB)
  if (BETWEEN(addr, 0x02000000, 0x0203FFFF)) {
    return read_ewram8(addr);
  }
  // WRAM (32KB)
  if (BETWEEN(addr, 0x03000000, 0x03007FFF)) {
    return read_iwram8(addr);
  }
  // IO
  if (BETWEEN(addr, 0x04000000, 0x40003FE)) {
    return read_io8(addr);
  }
  // BG/OBJ Palette RAM (1KB)
  if (BETWEEN(addr, 0x05000000, 0x050003FF)) {
    return ppu_read_bgobjram8(addr);
  }
  // VRAM (96KB)
  if (BETWEEN(addr, 0x06000000, 0x06017FFF)) {
    return ppu_read_vram8(addr);
  }
  // OAM (1KB)
  if (BETWEEN(addr, 0x07000000, 0x070003FF)) {
    return ppu_read_oam8(addr);
  }
  // ROM - Wait State 0, 1, and 2 (3 x 32MB)
  if (BETWEEN(addr, 0x08000000, 0x0E00FFFF)) {
    return cart_read_rom8(addr);
  }
  // Game Pak SRAM (64KB)
  if (BETWEEN(addr, 0x0E000000, 0x0E00FFFF)) {
    return cart_read_ram8(addr);
  }

  fprintf(stderr, "Invalid read: %08X\n", addr);
  exit(EXIT_FAILURE);
}

void bus_write16(uint32_t addr, uint16_t val) {
  uint8_t b1 = (val & 0x00FF);
  uint8_t b2 = (val & 0xFF00) >> 8;
  bus_write8(addr, b1);
  bus_write8(addr + 1, b2);
}

void bus_write32(uint32_t addr, uint32_t val) {}

void bus_write8(uint32_t addr, uint8_t val) {
  // WRAM (256KB)
  if (BETWEEN(addr, 0x02000000, 0x0203FFFF)) {
    write_ewram8(addr, val);
  }
  // WRAM (32KB)
  if (BETWEEN(addr, 0x03000000, 0x03007FFF)) {
    write_iwram8(addr, val);
  }
  // IO
  if (BETWEEN(addr, 0x04000000, 0x40003FE)) {
    write_io8(addr, val);
  }
  // BG/OBJ Palette RAM (1KB)
  if (BETWEEN(addr, 0x05000000, 0x050003FF)) {
    ppu_write_bgobjram8(addr, val);
  }
  // VRAM (96KB)
  if (BETWEEN(addr, 0x06000000, 0x06017FFF)) {
    ppu_write_vram8(addr, val);
  }
  // OAM (1KB)
  if (BETWEEN(addr, 0x07000000, 0x070003FF)) {
    ppu_write_oam8(addr, val);
  }
  // ROM - Wait State 0, 1, and 2 (3 x 32MB)
  if (BETWEEN(addr, 0x08000000, 0x0E00FFFF)) {
    fprintf(stderr, "Invalid write (Cannot write to GamePak ROM): %08X\n",
            addr);
    exit(EXIT_FAILURE);
  }
  // Game Pak SRAM (64KB)
  if (BETWEEN(addr, 0x0E000000, 0x0E00FFFF)) {
    cart_write_ram8(addr, val);
  }
  if (!BETWEEN(addr, 0x00000000, 0x0E00FFFF)) {
    fprintf(stderr, "Invalid write: %08X\n", addr);
    exit(EXIT_FAILURE);
  }
}
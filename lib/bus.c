#include <bus.h>
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

uint8_t bus_read8(uint32_t addr) {
  // WRAM (256KB)
  if (BETWEEN(addr, 0x02000000, 0x0203FFFF)) {
    NO_IMPL
  }
}
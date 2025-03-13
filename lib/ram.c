#include <ram.h>

static ram_context ctx;

uint16_t read_wram(uint32_t addr) {
    addr -= WRAM_START;

    if (addr < 0x00 || addr >= WRAM_SIZE) {
        printf("INVALID WRAM ADDR %08X\n", addr + 0x02000000);
        exit(-1);
    }

    return ctx.wram[addr];
}

void write_wram(uint32_t addr, uint16_t val) {
    addr -= WRAM_START;

    if (addr < 0x00 || addr >= WRAM_SIZE) {
        printf("INVALID WRAM ADDR %08X\n", addr + 0x02000000);
        exit(-1);
    }

    ctx.wram[addr] = val;
}

uint32_t read_hram(uint32_t addr) {
    addr -= HRAM_START;

    if (addr < 0x00 || addr >= HRAM_SIZE) {
        printf("INVALID HRAM ADDR %08X\n", addr + 0x03000000);
        exit(-1);
    }

    return ctx.hram[addr];
}

void write_hram(uint32_t addr, uint16_t val) {
    addr -= HRAM_START;

    if (addr < 0x00 || addr >= HRAM_SIZE) {
        printf("INVALID HRAM ADDR %08X\n", addr + 0x03000000);
        exit(-1);
    }

    ctx.hram[addr] = val;
}
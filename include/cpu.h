#pragma once

#include <common.h>

typedef enum {
    R0 = 0x0,
    R1 = 0x1,
    R2 = 0x2,
    R3 = 0x3,
    R4 = 0x4,
    R5 = 0x5,
    R6 = 0x6,
    R7 = 0x7,
    R8 = 0x8,
    R9 = 0x9,
    R10 = 0xA,
    R11 = 0xB,
    R12 = 0xC,
    R13 = 0xD,
    R14 = 0xE,
} cpu_register_t;

typedef struct {
    uint32_t regs[15]; // r0 - r14
    uint32_t pc;          // program counter
    uint32_t cpsr;        // current program status register
    uint32_t spsr;        // saved program status register
    uint32_t instruction; // current instruction
    uint32_t cycle;      // current cycle count
    uint32_t wait;       // wait state
} cpu_context;

typedef enum {
    ARM,
    THUMB,
} cpu_state_t;

typedef enum {
    ARM_MODE_USER = 0x10,
    ARM_MODE_FIQ = 0x11,
    ARM_MODE_IRQ = 0x12,
    ARM_MODE_SVC = 0x13,
    ARM_MODE_ABT = 0x17,
    ARM_MODE_UND = 0x1B,
    ARM_MODE_SYS = 0x1F
} cpu_mode_t;

typedef enum {
    CPU_FLAG_N = 0x80000000, // Negative flag
    CPU_FLAG_Z = 0x40000000, // Zero flag
    CPU_FLAG_C = 0x20000000, // Carry flag
    CPU_FLAG_V = 0x10000000, // Overflow flag
    CPU_FLAG_I = 0x00000080, // IRQ disable flag
    CPU_FLAG_F = 0x00000040, // FIQ disable flag
    CPU_FLAG_T = 0x00000020, // Thumb state flag
} cpu_flag_t;

typedef void (*cpu_processor_t)(cpu_context *ctx);

/**
 * @brief Initialize the CPU context.
 * 
 */
void cpu_init();

/**
 * @brief Get the value of a specific CPU flag.
 * 
 * @param flag The flag to check.
 * @return true if the flag is set, false otherwise.
 */
bool get_cpu_flag(cpu_flag_t flag);

cpu_mode_t get_cpu_mode();
cpu_state_t get_cpu_state();
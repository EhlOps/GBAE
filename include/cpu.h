#pragma once

#include <common.h>

typedef struct {
    // General Purpose Registers
    u_int32_t R0;
    u_int32_t R1;
    u_int32_t R2;
    u_int32_t R3;
    u_int32_t R4;
    u_int32_t R5;
    u_int32_t R6;
    u_int32_t R7;
    u_int32_t R8;
    u_int32_t R9;
    u_int32_t R10;
    u_int32_t R11;
    u_int32_t R12;

    // Stack Pointer
    u_int32_t SP;

    // Link Register
    u_int32_t LR;

    // Program Counter
    u_int32_t PC;

    // Current Program Status Register
    u_int32_t CPSR;
} cpu_registers;
#pragma once

#include <common.h>
#include <cpu.h>

typedef enum {
    INSTURCTION_BRANCH_BRANCH_ECHANGE,
    INSTRUCTION_BLOCK_DATA_TRANSFER,
    INSTRUCTION_BRANCH_BRANCH_WITH_LINK,
    INSTRUCTION_SOFTWARE_INTERRUPT,
    INSTRUCTION_UNDEFINED,
    INSTRUCTION_SINGLE_DATA_TRANSFER,
    INSTRUCTION_SINGLE_DATA_SWAP,
    INSTRUCTION_MULTIPLY,
    INSTRUCTION_MULTIPLY_LONG,
    INSTRUCTION_HALFWORD_DATA_TRANSFER_REGISTER,
    INSTRUCTION_HALFWORD_DATA_TRANSFER_IMMEDIATE,
    INSTRUCTION_PSR_TRANSFER,
    INSTRUCTION_DATA_PROCESSING,
} ARMinstruction_type_t;

typedef enum {
    CONDITION_EQ = 0x0,  // Equal
    CONDITION_NE = 0x1,  // Not equal
    CONDITION_CS = 0x2,  // Carry set
    CONDITION_CC = 0x3,  // Carry clear
    CONDITION_MI = 0x4,  // Minus
    CONDITION_PL = 0x5,  // Plus
    CONDITION_VS = 0x6,  // Overflow
    CONDITION_VC = 0x7,  // No overflow
    CONDITION_HI = 0x8,  // Unsigned higher
    CONDITION_LS = 0x9,  // Unsigned lower or same
    CONDITION_GE = 0xA,  // Signed greater than or equal
    CONDITION_LT = 0xB,  // Signed less than
    CONDITION_GT = 0xC,  // Signed greater than
    CONDITION_LE = 0xD,  // Signed less than or equal
    CONDITION_AL = 0xE,  // Always (unconditional)
} ARMcondition_t;

typedef enum {
    AND = 0x0,
    EOR = 0x1,
    SUB = 0x2,
    RSB = 0x3,
    ADD = 0x4,
    ADC = 0x5,
    SBC = 0x6,
    RSC = 0x7,
    TST = 0x8,
    TEQ = 0x9,
    CMP = 0xA,
    CMN = 0xB,
    ORR = 0xC,
    MOV = 0xD,
    BIC = 0xE,
    MVN = 0xF,
} ARMopcode_t;

typedef struct {
    bool immediate; // true if immediate value
    bool shift;    // true if shifted register value
    union {
        struct {
            uint32_t immediate;
            uint8_t rotate; // amount of ROR applied
        } imm;
        struct {
            uint8_t Rm;        // Base register
            uint8_t shift_type; // 0 = LSL, 1 = LSR, 2 = ASR, 3 = ROR
            uint8_t shift_amount; // if shift by immediate
            uint8_t Rs;        // if shift by register (optional)
            bool shift_by_register;
        } reg;
    };
} ARMoperand2_t;

typedef struct {
    ARMcondition_t condition;  // top 4 bits
    ARMinstruction_type_t type;       // classify instruction (data proc, branch, load/store, etc.)

    // Additional fields based on type
    ARMopcode_t opcode;     // for data processing
    cpu_register_t rn, rd;     // register fields
    ARMoperand2_t operand2; // Operand2 field (immediate or register)
    int32_t offset;     // for branches
    bool set_flags;     // S bit
} ARMinstruction_t;

/**
 * @brief Decodes an ARM instruction from a 32-bit integer.
 * 
 * @param instruction 
 * @return ARMinstruction_t 
 */
ARMinstruction_t decode_arm_instruction(uint32_t instruction);

/**
 * @brief Get the processor object
 * 
 * @param inst 
 * @return cpu_processor_t 
 */
cpu_processor_t get_arm_processor(ARMinstruction_t *inst);
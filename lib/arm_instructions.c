#include <arm_instructions.h>
#include <cpu.h>
#include <common.h>

// Check if the instruction is a branch or branch exchange instruction
static bool is_branch_and_branch_exhange_instruction(uint32_t instruction) {
    uint32_t mask = 0b00000001001011111111111100010000;
    return (instruction & mask) == 0b00000001001011111111111100010000;
}

ARMinstruction_type_t decode_arm_instruction_type(uint32_t instruction) {
    return INSTRUCTION_UNDEFINED; // Default to undefined instruction
}

ARMinstruction_t decode_arm_instruction(uint32_t instruction) {
    ARMinstruction_t inst = {0}; // Initialize instruction structure

    inst.type = decode_arm_instruction_type(instruction); 

    switch (inst.type) {
        default:
            break;
    }

    return inst; // Return the decoded instruction
}
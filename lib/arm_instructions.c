#include <arm_instructions.h>
#include <common.h>
#include <cpu.h>

// Check if the instruction is a data processing instruction
static bool is_data_processing_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110000000000000000000000000;
  return (instruction & mask) == 0b00000010000000000000000000000000;
}

// Check if the instruction is a multiply instruction
static bool is_multiply_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111110000000000000011110000;
  return (instruction & mask) == 0b00000000000000000000000010010000;
}

// Check if the instruction is a multiply long instruction
static bool is_multiply_long_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111100000000000000011110000;
  return (instruction & mask) == 0b00000000100000000000000010010000;
}

// Check if instruction is a single data swap instruction
static bool is_single_data_swap_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111101100000000111111110000;
  return (instruction & mask) == 0b00000001000000000000000010010000;
}

// Check if the instruction is a branch and exchange instruction
static bool is_branch_and_exhange_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111111111111111111111110000;
  return (instruction & mask) == 0b00000001001011111111111100010000;
}

// Check if the instruction is a halfword data transfer register offset
// instruction
static bool
is_halfword_data_transfer_register_offset_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110010000000000000010010000;
  bool s_bit = BIT(instruction, 6);
  bool h_bit = BIT(instruction, 5);
  return (instruction & mask) == 0b00000000000000000000000010010000 &&
         (s_bit || h_bit);
}

// Check if the instruction is a halfword data transfer immediate offset
// instruction
static bool
is_halfword_data_transfer_immediate_offset_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110010000000000000010010000;
  bool s_bit = BIT(instruction, 6);
  bool h_bit = BIT(instruction, 5);
  return (instruction & mask) == 0b00000000010000000000000010010000 &&
         (s_bit || h_bit);
}

// Check if the instruction is a single data transfer instruction
static bool is_single_data_transfer_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110000000000000000000000000;
  return (instruction & mask) == 0b00000110000000000000000000000000;
}

// Check if the instruction is the undefined instruction
static bool is_undefined_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110000000000000000000010000;
  return (instruction & mask) == 0b00000110000000000000000000010000;
}

// Check if the instruction is a block data transfer instruction
static bool is_block_data_transfer_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110000000000000000000000000;
  return (instruction & mask) == 0b00001000000000000000000000000000;
}

// Check if the instruction is a branch instruction
static bool is_branch_instruction(uint32_t instruction) {
  uint32_t mask = 0b0000111000000000000000000000000000;
  return (instruction & mask) == 0b00001010000000000000000000000000000;
}

// Check if the instruction is a coprocessor data transfer instruction
static bool is_coprocessor_data_transfer_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001110000000000000000000000000;
  return (instruction & mask) == 0b00001100000000000000000000000000;
}

// Check if the instruction is a coprocessor data operatiuon instruction
static bool is_coprocessor_data_operation_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111000000000000000000010000;
  return (instruction & mask) == 0b00001110000000000000000000000000;
}

// Check if the instruction is a coprocessor register transfer instruction
static bool is_coprocessor_register_transfer_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111000000000000000000010000;
  return (instruction & mask) == 0b00001110000000000000000000010000;
}

// Check if the instruction is a software interrupt instruction
static bool is_software_interrupt_instruction(uint32_t instruction) {
  uint32_t mask = 0b00001111000000000000000000000000;
  return (instruction & mask) == 0b00001111000000000000000000000000;
}

ARMinstruction_type_t decode_arm_instruction_type(uint32_t instruction) {
  if (is_data_processing_instruction(instruction)) {
    return INSTRUCTION_DATA_PROC;
  } else if (is_multiply_instruction(instruction)) {
    return INSTRUCTION_MULTIPLY;
  } else if (is_multiply_long_instruction(instruction)) {
    return INSTRUCTION_MULTIPLY_LONG;
  } else if (is_single_data_swap_instruction(instruction)) {
    return INSTRUCTION_SINGLE_DATA_SWAP;
  } else if (is_branch_and_exhange_instruction(instruction)) {
    return INSTRUCTION_BRANCH_AND_EXCHANGE;
  } else if (is_halfword_data_transfer_register_offset_instruction(
                 instruction)) {
    return INSTRUCTION_HALFWORD_DATA_TRANSFER_REGISTER_OFFSET;
  } else if (is_halfword_data_transfer_immediate_offset_instruction(
                 instruction)) {
    return INSTRUCTION_HALFWORD_DATA_TRANSFER_IMMEDIATE_OFFSET;
  } else if (is_single_data_transfer_instruction(instruction)) {
    return INSTRUCTION_SINGLE_DATA_TRANSFER;
  } else if (is_undefined_instruction(instruction)) {
    return INSTRUCTION_UNDEFINED;
  } else if (is_block_data_transfer_instruction(instruction)) {
    return INSTRUCTION_BLOCK_DATA_TRANSFER;
  } else if (is_branch_instruction(instruction)) {
    return INSTRUCTION_BRANCH;
  } else if (is_coprocessor_data_transfer_instruction(instruction)) {
    return INSTRUCTION_COPROCESSOR_DATA_TRANSFER;
  } else if (is_coprocessor_data_operation_instruction(instruction)) {
    return INSTRUCTION_COPROCESSOR_DATA_OP;
  } else if (is_coprocessor_register_transfer_instruction(instruction)) {
    return INSTRUCTION_COPROCESSOR_REGISTER_TRANSFER;
  } else if (is_software_interrupt_instruction(instruction)) {
    return INSTRUCTION_SOFTWARE_INTERRUPT;
  }

  // Print an error message if the instruction type is not recognized
  fprintf(stderr, "Unknown instruction type: 0x%08x\n", instruction);
  // If no instruction type matches, print an error and exit
  exit(EXIT_FAILURE); // Exit if no instruction type matches
}

ARMinstruction_t decode_arm_instruction(uint32_t instruction) {
  ARMinstruction_t inst = {0}; // Initialize instruction structure

  inst.type = decode_arm_instruction_type(instruction);

  return inst; // Return the decoded instruction
}
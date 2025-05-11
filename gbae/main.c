#include <SDL3/SDL.h>
#include <arm_instructions.h>
#include <bus.h>
#include <cart.h>
#include <cpu.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must have 2 args...\n");
    return 1;
  }

  SDL_Thread *cpu_thread;

  cpu_thread = SDL_CreateThread((void *)cart_save_ram, "Save cart ram", NULL);

  if (cart_load(argv[1])) {
    printf("Cart loaded successfully...\n");
  }

  cpu_init();
  printf("CPU initialized...\n");

  printf("CPU mode: 0x%x\n", get_cpu_mode());
  printf("CPU state: %s\n", get_cpu_state() ? "THUMB" : "ARM");

  uint32_t instruction = bus_read32(0x080000C0);
  printf("Instruction: 0x%08x\n", instruction);
  ARMinstruction_t instruction_type = decode_arm_instruction(instruction);
  printf("Instruction type: %d\n", instruction_type.type);

  return 0;
}

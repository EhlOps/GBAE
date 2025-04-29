#include <common.h>
#include <cpu.h>

// CPU: ARM7TDMI

static cpu_context ctx;

extern cpu_mode_t mode;

void cpu_init() {
  ctx.cpsr = 0x0000001F; // Set CPSR to default value
  ctx.pc = 0x08000000; // Set PC to start of ROM
  ctx.cycle = 0; // Initialize cycle count
  ctx.wait = 0; // Initialize wait state
}

bool get_cpu_flag(cpu_flag_t flag) {
  return (ctx.cpsr & flag) != 0; // Check if the specified flag is set in CPSR
}

cpu_mode_t get_cpu_mode() {
  return (cpu_mode_t)(ctx.cpsr & 0x1F); // Get current CPU mode from CPSR
}

cpu_state_t get_cpu_state() {
  return get_cpu_flag(CPU_FLAG_T) ? THUMB : ARM; // Get current CPU state from CPSR
}

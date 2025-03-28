#include <gamepad.h>

typedef struct {
  bool button_sel;
  bool direction_sel;
  gamepad_state state;
} gamepad_context;

static gamepad_context ctx = {0};

bool gamepad_button_sel() { return ctx.button_sel; }

bool gamepad_direction_sel() { return ctx.direction_sel; }

void gamepad_set_input(uint16_t input) {
  ctx.button_sel = input & 0x20;
  ctx.direction_sel = input & 0x10;
}

gamepad_state *gamepad_get_state() { return &ctx.state; }

uint16_t gamepad_get_output() {
  uint16_t output = 0x01FF;

  if (!gamepad_button_sel()) {
    if (ctx.state.a) {
      output &= ~0x01;
    }
    if (ctx.state.b) {
      output &= ~0x02;
    }
    if (ctx.state.select) {
      output &= ~0x04;
    }
    if (ctx.state.start) {
      output &= ~0x08;
    }
    if (ctx.state.r) {
      output &= ~0x10;
    }
    if (ctx.state.l) {
      output &= ~0x20;
    }
  }
  if (!gamepad_direction_sel()) {
    if (ctx.state.up) {
      output &= ~0x40;
    }
    if (ctx.state.down) {
      output &= ~0x80;
    }
    if (ctx.state.left) {
      output &= ~0x100;
    }
    if (ctx.state.right) {
      output &= ~0x200;
    }
  }

  return output;
}
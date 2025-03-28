#include <gamepad.h>

typedef struct {
  bool button_sel;
  bool direction_sel;
  gamepad_state state;
} gamepad_context;

static gamepad_context ctx = {0};

/**
 * @brief Returns the state of a button being pressed.
 *
 * @return true if a button is pressed.
 * @return false if a button is not pressed.
 */
bool gamepad_button_sel() { return ctx.button_sel; }

/**
 * @brief Returns the state of the direction pad being selected.
 *
 * @return true if the direction pad is selected.
 * @return false if the direction pad is not selected.
 */
bool gamepad_direction_sel() { return ctx.direction_sel; }

/**
 * @brief Sets the input of the gamepad context.
 *
 * @param input The input to set.
 */
void gamepad_set_input(uint16_t input) {
  ctx.button_sel = input & 0x20;
  ctx.direction_sel = input & 0x10;
}

/**
 * @brief Returns the state of the gamepad.
 *
 * @return gamepad_state* The state of the gamepad.
 */
gamepad_state *gamepad_get_state() { return &ctx.state; }

/**
 * @brief Returns the output of the gamepad.
 *
 * @return uint16_t The output of the gamepad as a 16 bit integer.
 */
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
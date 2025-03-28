#pragma once

#include <common.h>

typedef struct {
  bool l;
  bool r;
  bool a;
  bool b;
  bool start;
  bool select;
  bool up;
  bool down;
  bool left;
  bool right;
} gamepad_state;

/**
 * @brief Returns the state of a button being pressed.
 *
 * @return true if a button is pressed.
 * @return false if a button is not pressed.
 */
bool gamepad_button_sel();

/**
 * @brief Returns the state of the direction pad being selected.
 *
 * @return true if the direction pad is selected.
 * @return false if the direction pad is not selected.
 */
bool gamepad_direction_sel();

/**
 * @brief Sets the input of the gamepad context.
 *
 * @param input The input to set.
 */
void gamepad_set_input(uint16_t input);

/**
 * @brief Returns the state of the gamepad.
 *
 * @return gamepad_state* The state of the gamepad.
 */
gamepad_state *gamepad_get_state();

/**
 * @brief Returns the output of the gamepad.
 *
 * @return uint16_t The output of the gamepad as a 16 bit integer.
 */
uint16_t gamepad_get_output();
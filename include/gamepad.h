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

bool gamepad_button_sel();
bool gamepad_direction_sel();
void gamepad_set_input(uint16_t input);
gamepad_state *gamepad_get_state();
uint16_t gamepad_get_output();
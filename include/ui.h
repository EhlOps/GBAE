#pragma once

#include <common.h>

#define UI_WIDTH 240
#define UI_HEIGHT 160


/**
 * @brief Initialize the UI
 * 
 */
void ui_init();

/**
 * @brief Handle the events to create UI updates
 * 
 */
void ui_handle_events();

/**
 * @brief Update the UI
 * 
 */
void ui_update();
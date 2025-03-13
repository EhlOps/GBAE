#pragma once
#include <common.h>

#define GBA_CLOCK_FREQ 16.776e6f
#define GBA_SCREEN_REFRESH_RATE 59.7275f
#define GBA_CLOCK_CYCLES_PER_FRAME (GBA_CLOCK_FREQ / GBA_SCREEN_REFRESH_RATE)

float display_frequency();
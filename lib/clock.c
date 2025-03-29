#include <SDL3/SDL.h>
#include <clock.h>

float display_frequency() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 0;
  }
  return 0;
}
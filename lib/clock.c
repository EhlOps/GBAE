#include <SDL3/SDL.h>
#include <clock.h>

float display_frequency() {
  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    fprintf(stderr, "Unable to initialize SDL: %s", SDL_GetError());
    return 0;
  }
  return 0;
}
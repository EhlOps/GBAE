#include <SDL3/SDL.h>
#include <ui.h>

SDL_Window *window;
SDL_Renderer *renderer;

static u_int8_t scale = 4;

void ui_init() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == false) {
    SDL_Log("SDL_Init: %s", SDL_GetError());
    return;
  }

  window = SDL_CreateWindow("GBAE", UI_WIDTH * scale, UI_HEIGHT * scale, 0);
  if (window == NULL) {
    SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
    return;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == NULL) {
    SDL_Log("SDL_CreateRenderer: %s", SDL_GetError());
    return;
  }

  SDL_Event event;
  uint8_t quit = 0;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        SDL_Log("SDL3 Event: Quit");
        quit = 1;
        break;
      case SDL_EVENT_KEY_DOWN:
        if (event.key.key == SDLK_ESCAPE) {
          SDL_Log("SDL3 ESC Key Quit");
          quit = 1;
        }
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }

  SDL_Log("SDL3 Shutdown");

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

void ui_handle_events() { NO_IMPL }

void ui_update() { NO_IMPL }
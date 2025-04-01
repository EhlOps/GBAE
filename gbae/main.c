#include <SDL3/SDL.h>
#include <cart.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must have 2 args...\n");
    return 1;
  }

  SDL_Thread *cpu_thread;

  cpu_thread = SDL_CreateThread((void *)cart_save_ram, "Save cart ram", NULL);

  if (cart_load(argv[1])) {
    printf("Cart loaded successfully...\n");
  }

  return 0;
}

#include <cart.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must have 2 args...\n");
    return 1;
  }
  if (cart_load(argv[1])) {
    printf("Cart loaded successfully...\n");
  }

  cart_save_ram();
}

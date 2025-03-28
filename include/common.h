#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BIT(a, n) ((a & (1 << (n)) ? 1 : 0))

#define SET_BIT(a, n, on)                                                      \
  {                                                                            \
    if (on)                                                                    \
      a |= (1 << n);                                                           \
    else                                                                       \
      a &= ~(1 << n);                                                          \
  }

#define BETWEEN(a, b, c) ((a) >= (b) && (a) <= (c))

#define NO_IMPL                                                                \
  {                                                                            \
    printf("No implementation\n");                                             \
    exit(1);                                                                   \
  }
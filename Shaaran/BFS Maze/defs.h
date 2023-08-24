#ifndef _MAP_H
#define _MAP_H

#include <stddef.h>
#include <stdint.h>

#define MAX_PATH_SIZE 285
#define MAP_WIDTH 19
#define MAP_HEIGHT 15

typedef struct Point {
  uint8_t x, y;
} Point;

typedef struct Stack {
  uint8_t top, cap;
  Point *array;
} Stack;
#endif // _MAP_H

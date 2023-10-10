#ifndef _MAP_H
#define _MAP_H

#include <stddef.h>
#include <stdint.h>

#define MAX_PATH_SIZE 128
#define MAP_WIDTH 19
#define MAP_HEIGHT 15
#define IGNORE 0
#define UPTURN    1
#define DOWNTURN  2
#define LEFTTURN  3
#define RIGHTTURN 4

typedef struct Point {
  uint8_t x, y,direction,node,finalTurn,foodPoint,steps;
} Point;

#endif // _MAP_H

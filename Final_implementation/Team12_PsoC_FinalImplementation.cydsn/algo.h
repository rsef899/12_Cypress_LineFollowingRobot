#ifndef _ALGO_H
#define _ALGO_H

#include "defines.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct AlgoResult {
  size_t pathLength;
} AlgoResult;

size_t run_algo(const uint8_t map[MAP_HEIGHT][MAP_WIDTH],
                    Point start,
                    const Point *ends,
                    size_t endCount,
                    Point *outPath);

uint8_t point_eq(Point a, Point b);
uint8_t whichDirection(Point a, Point b);


#endif // _ALGO_H

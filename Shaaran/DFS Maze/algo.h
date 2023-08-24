#ifndef _ALGO_H
#define _ALGO_H

#include "defs.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct AlgoResult {
  size_t pathLength;
} AlgoResult;

AlgoResult run_algo(const uint8_t map[MAP_HEIGHT][MAP_WIDTH],
                    Point start,
                    const Point *ends,
                    size_t endCount,
                    Point *outPath);

uint8_t point_eq(Point a, Point b);


#endif // _ALGO_H

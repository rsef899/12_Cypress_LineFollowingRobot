#include "algo.h"
#include "defs.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Macros that allow easy creation of adjacent points
// i.e. LEFT(start), will get you the position that is
// left from the starting point.

#define LEFT(p) ((Point){.x = (p).x - 1, .y = (p).y})
#define RIGHT(p) ((Point){.x = (p).x + 1, .y = (p).y})
#define ABOVE(p) ((Point){.x = (p).x, .y = (p).y - 1})
#define BELOW(p) ((Point){.x = (p).x, .y = (p).y + 1})

// INPUTS
// map:
//	 The map to be used to run BFS on
// start:
//	 Start points for the algorithm
// ends:
//   The end points which the algorithm should search for
// endCount:
//	 The number of possible end points we have (size of array ends points to)
// out:
//   Where your final path should be written. It is an array.
//
// RETURNS:
//  The length of the path
AlgoResult run_algo(const uint8_t map[MAP_HEIGHT][MAP_WIDTH],
                    Point start,
                    const Point *ends,
                    size_t endCount,
                    Point *out) {
  Point visited[MAP_HEIGHT][MAP_WIDTH] = {{0}};
  uint8_t dummyMap[MAP_HEIGHT][MAP_WIDTH];
  for (uint8_t i = 0; i < MAP_HEIGHT; i++) {
    for (uint8_t j = 0; j < MAP_WIDTH; j++) {
      dummyMap[i][j] = map[i][j];
    }
  }
  Point foundEnds[endCount];
  size_t foundEndsCount = 0;
  uint16_t outIndex = 0;
  // out[outIndex++] = start;
  Point stack[MAP_HEIGHT * MAP_WIDTH];
  size_t stackTop = 0;
  stack[stackTop++] = start;
  Point newStart = start;

  while (stackTop > 0) {
    uint8_t found = 0;
    Point curr = stack[--stackTop];
    Point left = LEFT(curr);
    Point right = RIGHT(curr);
    Point above = ABOVE(curr);
    Point below = BELOW(curr);
    for (uint8_t j = 0; j < endCount; j++) {
      if (point_eq(curr, ends[j])) {
        for (uint16_t i = 0; i < endCount; i++) {
          if (point_eq(curr, foundEnds[i])) {
            found = 1;
          }
        }
        if (found == 0) {
          Point shortestPath[MAP_HEIGHT * MAP_WIDTH];
          size_t shortestPathIndex = 0;
          Point traceBack = curr;

          while (!point_eq(traceBack, newStart)) {
            shortestPath[shortestPathIndex++] = traceBack;
            traceBack = visited[traceBack.y][traceBack.x];
          }

          shortestPath[shortestPathIndex++] = newStart;

          // Copy the reconstructed path to the 'out' array
          for (int i = shortestPathIndex - 1; i >= 0; i--) {
            out[outIndex++] = shortestPath[i];
          }

          // Reset visited array for the next search
          for (uint8_t i = 0; i < MAP_HEIGHT; i++) {
            for (uint8_t j = 0; j < MAP_WIDTH; j++) {
              visited[i][j] = (Point){0};
              dummyMap[i][j] = map[i][j];
            }
          }

          newStart = curr;
          foundEnds[foundEndsCount] = curr;
          // Increment the found ends count:
          foundEndsCount++;

          if (foundEndsCount == endCount) {
            // Return the shortest path length
            return (AlgoResult){.pathLength = outIndex};
          }
        }
      }
    }
    // Mark the current node as visited (non-zero)
    dummyMap[curr.y][curr.x] = 1;
    if (dummyMap[left.y][left.x] == 0) {
      stack[stackTop++] = left;
      visited[left.y][left.x] = curr; // Store the parent
    }
    if (dummyMap[right.y][right.x] == 0) {
      stack[stackTop++] = right;
      visited[right.y][right.x] = curr; // Store the parent
    }
    if (dummyMap[above.y][above.x] == 0) {
      stack[stackTop++] = above;
      visited[above.y][above.x] = curr; // Store the parent
    }
    if (dummyMap[below.y][below.x] == 0) {
      stack[stackTop++] = below;
      visited[below.y][below.x] = curr; // Store the parent
    }
  }
  return (AlgoResult){.pathLength = 0};
}

// Don't need to modify this
uint8_t point_eq(Point a, Point b) { return a.x == b.x && a.y == b.y; }

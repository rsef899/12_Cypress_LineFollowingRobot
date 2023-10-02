
// finds shortes path from start to first endpoint
#include "algo.h"
#include "defs.h"

#include <assert.h>
#include <stdint.h>
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
//	 The number of possible end points we have (size of array ends points
// to)
// out:
//   Where your final path should be written. It is an array.
//
// RETURNS:
//  The length of the path
bool isValid(Point p, const uint8_t map[MAP_HEIGHT][MAP_WIDTH]) {
  return p.x >= 0 && p.x < MAP_WIDTH && p.y >= 0 && p.y < MAP_HEIGHT &&
         map[p.y][p.x] == 0;
}
Point queue[MAP_HEIGHT * MAP_WIDTH];
size_t front = 0;
size_t rear = 0;
size_t size = 0;

bool isQueueEmpty() { return size == 0; }

bool isQueueFull() { return size == MAP_HEIGHT * MAP_WIDTH; }

void enqueue(Point element) {
  if (!isQueueFull()) {
    queue[rear] = element;
    rear = (rear + 1) % (MAP_HEIGHT * MAP_WIDTH);
    size++;
  }
}

Point dequeue() {
  Point element = {0}; // Default initialization
  if (!isQueueEmpty()) {
    element = queue[front];
    front = (front + 1) % (MAP_HEIGHT * MAP_WIDTH);
    size--;
  }
  return element;
}
size_t bfs(const uint8_t map[MAP_HEIGHT][MAP_WIDTH], Point start,
           const Point *ends, size_t endCount, Point *out) {
  Point visited[MAP_HEIGHT][MAP_WIDTH] = {{0}};
  uint8_t dummyMap[MAP_HEIGHT][MAP_WIDTH];
  for (uint8_t i = 0; i < MAP_HEIGHT; i++) {
    for (uint8_t j = 0; j < MAP_WIDTH; j++) {
      dummyMap[i][j] = map[i][j];
    }
  }
  uint8_t found = 0;
  size_t pathIndex = 0;
  uint8_t foundEndsCount = 0;
  //Point foundEnds[endCount];
  Point newStart = start;
  enqueue(start);

  while (!isQueueEmpty()) {
    Point curr = dequeue();
    Point left = LEFT(curr);
    Point right = RIGHT(curr);
    Point above = ABOVE(curr);
    Point below = BELOW(curr);
    
      if (point_eq(curr, ends[foundEndsCount])) {
          // Reconstruct the path to the endpoint
          Point shortestPath[MAP_HEIGHT*MAP_WIDTH];
          size_t shortestPathIndex = 0;
          Point traceBack = curr;
          uint8_t finalFound = 0;
          while (!point_eq(traceBack, newStart)) {
            if (traceBack.essentialNode == 1 && finalFound == 0) {
              traceBack.finalNode = 1;
              finalFound = 1;
            }
            shortestPath[shortestPathIndex++] = traceBack;
            traceBack = visited[traceBack.y][traceBack.x];
          }

          shortestPath[shortestPathIndex++] = newStart;

          // Copy the reconstructed path to the 'out' array
          for (int i = shortestPathIndex - 1; i >= 0; i--) {
            out[pathIndex++] = shortestPath[i];
          }

          // Reset visited array for the next search
          for (uint8_t i = 0; i < MAP_HEIGHT; i++) {
            for (uint8_t j = 0; j < MAP_WIDTH; j++) {
              visited[i][j] = (Point){0};
              dummyMap[i][j] = map[i][j];
            }
          }
          front = 0;
          rear = 0;
          size = 0;

          newStart = curr;
          //foundEnds[foundEndsCount] = curr;
          // Increment the found ends count:
          foundEndsCount++;

          if (foundEndsCount == endCount) {
            // Return the shortest path length
            return pathIndex;
          }
        }
    dummyMap[curr.y][curr.x] = 1;
    uint8_t pointsValid = 0;
    if (isValid(left, dummyMap)) {
      left.direction = LEFTTURN;
      pointsValid++;
      enqueue(left);
      if (pointsValid >= 2 || (curr.direction != LEFTTURN)) { // If more than two points valid it is a node
        curr.essentialNode = 1;
      }
      visited[left.y][left.x] = curr; // Store the parent
    }
    if (isValid(right, dummyMap)) {
      right.direction = RIGHTTURN;
      pointsValid++;
      if (pointsValid >= 2 || (curr.direction != RIGHTTURN)) { // If more than two points valid it is a node
        curr.essentialNode = 1;
      }
      enqueue(right);
      visited[right.y][right.x] = curr; // Store the parent
    }
    if (isValid(above, dummyMap)) {
      above.direction = UPTURN;
      pointsValid++;
      if (pointsValid >= 2 || (curr.direction != UPTURN)) { // If more than two points valid it is a node
        curr.essentialNode = 1;
      }
      enqueue(above);
      visited[above.y][above.x] = curr; // Store the parent
    }
    if (isValid(below, dummyMap)) {
      below.direction = DOWNTURN;
      pointsValid++;
      if (pointsValid >= 2 || (curr.direction != DOWNTURN)) { // If more than two points valid it is a node
        curr.essentialNode = 1;
      }
      enqueue(below);
      visited[below.y][below.x] = curr; // Store the parent
    }
    

    
  }
  return 0;
}

AlgoResult run_algo(const uint8_t map[MAP_HEIGHT][MAP_WIDTH], Point start,
                    const Point *ends, size_t endCount, Point *out) {
  size_t pathLength = bfs(map, start, ends, endCount, out);
  return (AlgoResult){.pathLength = pathLength};
}

// Don't need to modify this
uint8_t point_eq(Point a, Point b) { return a.x == b.x && a.y == b.y; }

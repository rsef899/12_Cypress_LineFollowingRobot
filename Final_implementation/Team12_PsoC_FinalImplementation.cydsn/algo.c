// finds shortes path from start to first endpoint
#include "algo.h"
#include "defines.h"

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
    // left.direction = (curr.direction == RIGHTTURN) ? DOWNTURN : (curr.direction == LEFTTURN) ? UPTURN : (curr.direction == UPTURN) ? LEFTTURN : RIGHTTURN;

    // right.direction = (curr.direction == RIGHTTURN) ? UPTURN : (curr.direction == LEFTTURN) ? DOWNTURN : (curr.direction == UPTURN) ? RIGHTTURN : LEFTTURN;
    // above.direction = (curr.direction == RIGHTTURN) ? LEFTTURN : (curr.direction == LEFTTURN) ? RIGHTTURN : (curr.direction == UPTURN) ? UPTURN : DOWNTURN;
    // below.direction = (curr.direction == RIGHTTURN) ? RIGHTTURN : (curr.direction == LEFTTURN) ? LEFTTURN : (curr.direction == UPTURN) ? DOWNTURN : UPTURN;

    
      if (point_eq(curr, ends[foundEndsCount])) {
          // Reconstruct the path to the endpoint
          Point shortestPath[MAP_HEIGHT*MAP_WIDTH];
          size_t shortestPathIndex = 0;
          Point traceBack = curr;

          traceBack.foodPoint = 1; // Saying it is a foodpoint
          uint8_t finalFound = 0;
          uint8_t steps = 0;
          while (!point_eq(traceBack, newStart)) {
            Point traceLeft = LEFT(traceBack);
            
            Point traceRight = RIGHT(traceBack);
            Point traceUp = ABOVE(traceBack);
            Point traceBelow = BELOW(traceBack);
            if (traceBack.node == 1 && finalFound == 0) {
              traceBack.steps = steps;
              traceBack.finalTurn = 1;
              if (traceBack.x == curr.x) {
                traceBack.xOrY = VERTICAL;
              } else {
                traceBack.xOrY = HORIZONTAL; 
              }
              finalFound = 1;
            }
            if (finalFound==0) {
              steps++;
              if (point_eq(curr,traceBack)) {
                shortestPath[shortestPathIndex++] = traceBack;
              }
              //shortestPath[shortestPathIndex++] = traceBack;
              
            } else if (traceBack.node == 1) {
              shortestPath[shortestPathIndex++] = traceBack;
            }
            else if (((isValid(traceLeft,map) || isValid(traceRight,map))  && (isValid(traceBelow,map) || isValid(traceUp,map))) && !traceBack.node) {
              traceBack.node = 1;
              traceBack.direction = IGNORE;
              shortestPath[shortestPathIndex++] = traceBack;
            }
            traceBack = visited[traceBack.y][traceBack.x];
          }
          uint8_t pointsValid = 0;
          if ((isValid(LEFT(newStart),map) || isValid(RIGHT(newStart),map))  && ((isValid(BELOW(newStart),map)) || isValid(ABOVE(newStart),map))) {
            newStart.node = 1;
          }
          shortestPath[shortestPathIndex++] = newStart;
          

          // Copy the reconstructed path to the 'out' array
          for (int i = shortestPathIndex - 1; i >= 0; i--) {
            uint8_t direction = 0;
            if (i != 0) {
              if (shortestPath[i].direction == IGNORE) {
                shortestPath[i].direction = UPTURN;
              } else {
                if (shortestPath[i-1].direction == LEFTTURN) {
                  printf("here\n");
                  direction = (shortestPath[i].direction == RIGHTTURN) ? DOWNTURN : (shortestPath[i].direction == LEFTTURN) ? UPTURN : (shortestPath[i].direction == UPTURN) ? LEFTTURN : RIGHTTURN;
                  shortestPath[i].direction = direction;
                } else if (shortestPath[i-1].direction==RIGHTTURN) {
                  direction = (shortestPath[i].direction == RIGHTTURN) ? UPTURN : (shortestPath[i].direction == LEFTTURN) ? DOWNTURN : (shortestPath[i].direction == UPTURN) ? RIGHTTURN : LEFTTURN;
                  shortestPath[i].direction = direction;
                } else if (shortestPath[i-1].direction==UPTURN) {
                  direction = (shortestPath[i].direction == RIGHTTURN) ? LEFTTURN : (shortestPath[i].direction == LEFTTURN) ? RIGHTTURN : (shortestPath[i].direction == UPTURN) ? UPTURN : DOWNTURN;
                  shortestPath[i].direction = direction;
                } else if (shortestPath[i-1].direction==DOWNTURN){
                  direction = (shortestPath[i].direction == RIGHTTURN) ? RIGHTTURN : (shortestPath[i].direction == LEFTTURN) ? LEFTTURN : (shortestPath[i].direction == UPTURN) ? DOWNTURN : UPTURN;
                  shortestPath[i].direction = direction;
                } else { // if its an ignore
                  // direction = UPTURN;
                  // shortestPath[i-1].direction = UPTURN;
                  if (shortestPath[i-2].direction == LEFTTURN) {
                    printf("here\n");
                    direction = (shortestPath[i].direction == RIGHTTURN) ? DOWNTURN : (shortestPath[i].direction == LEFTTURN) ? UPTURN : (shortestPath[i].direction == UPTURN) ? LEFTTURN : RIGHTTURN;
                    shortestPath[i].direction = direction;
                  } else if (shortestPath[i-2].direction==RIGHTTURN) {
                    direction = (shortestPath[i].direction == RIGHTTURN) ? UPTURN : (shortestPath[i].direction == LEFTTURN) ? DOWNTURN : (shortestPath[i].direction == UPTURN) ? RIGHTTURN : LEFTTURN;
                    shortestPath[i].direction = direction;
                  } else if (shortestPath[i-2].direction==UPTURN) {
                    direction = (shortestPath[i].direction == RIGHTTURN) ? LEFTTURN : (shortestPath[i].direction == LEFTTURN) ? RIGHTTURN : (shortestPath[i].direction == UPTURN) ? UPTURN : DOWNTURN;
                    shortestPath[i].direction = direction;
                  } else if (shortestPath[i-2].direction==DOWNTURN){
                    direction = (shortestPath[i].direction == RIGHTTURN) ? RIGHTTURN : (shortestPath[i].direction == LEFTTURN) ? LEFTTURN : (shortestPath[i].direction == UPTURN) ? DOWNTURN : UPTURN;
                    shortestPath[i].direction = direction;
                    
                  }
                }
            }

            
            out[pathIndex++] = shortestPath[i];
            
            

          }
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
            
            
            if ((isValid(LEFT(curr),map) || isValid(RIGHT(curr),map))  && ((isValid(BELOW(curr),map)) || isValid(ABOVE(curr),map))) {
              curr.node = 1;
            }
            curr.foodPoint = 1;
            out[pathIndex++] = curr;
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
        curr.node = 1;
      }
      visited[left.y][left.x] = curr; // Store the parent
    }
    if (isValid(right, dummyMap)) {
      right.direction = RIGHTTURN;
      pointsValid++;
      if (pointsValid >= 2 || (curr.direction != RIGHTTURN)) { // If more than two points valid it is a node
        curr.node = 1;
      }
      enqueue(right);
      visited[right.y][right.x] = curr; // Store the parent
    }
    if (isValid(above, dummyMap)) {
      above.direction = UPTURN;
      pointsValid++;
      if (pointsValid >= 2 || (curr.direction != UPTURN)) { // If more than two points valid it is a node
        curr.node = 1;
      }
      enqueue(above);
      visited[above.y][above.x] = curr; // Store the parent
    }
    if (isValid(below, dummyMap)) {
      below.direction = DOWNTURN;
      pointsValid++;
      if (pointsValid >= 2 || (curr.direction != DOWNTURN)) { // If more than two points valid it is a node
        curr.node = 1;
      }
      enqueue(below);
      visited[below.y][below.x] = curr; // Store the parent
    }
    

    
  }
  return 0;
}

size_t run_algo(const uint8_t map[MAP_HEIGHT][MAP_WIDTH], Point start,
                    const Point *ends, size_t endCount, Point *out) {
  return bfs(map, start, ends, endCount, out);

}

uint8_t whichDirection(Point a, Point b) { // a is current, b is where we are going
  if (a.x > b.x) {
    return LEFTTURN;
  } else if (b.x>a.x) {
    return RIGHTTURN;
  } else if (b.y > a.y) {
    return UPTURN;
  } else {
    return DOWNTURN;
  }
}

// Don't need to modify this

uint8_t point_eq(Point a, Point b) { return a.x == b.x && a.y == b.y; }
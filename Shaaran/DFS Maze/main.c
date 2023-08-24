#include "algo.h"
#include "defs.h"
#include <assert.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SCALE 30
#define T(x) ((x)*GRID_SCALE)
#define COUNT_OF(x)                                                                    \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

static uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

/* static uint8_t map[MAP_HEIGHT][MAP_WIDTH] = { */
/*     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, */
/*     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, */
/* }; */

static Point food_list[] = {{1, 9}, {5, 5}, {7, 1}, {13, 5}, {9, 9}};

// Pre-declaration for functions defined later on
void visualise_map(uint8_t map[MAP_HEIGHT][MAP_WIDTH], int startx, int starty);
void draw_path(Point *path, int pathLength, int startx, int starty);
AlgoResult find_full_path(Point start, Point *out, size_t outCap);

int main(int argc, char **argv) {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(40 + MAP_WIDTH * GRID_SCALE,
             60 + MAP_HEIGHT * GRID_SCALE,
             "Robot Visualiser - 301");

  static const Point start = (Point){.x = 7, .y = MAP_HEIGHT - 2};
  static Point pathArray[MAX_PATH_SIZE];

  // Find the quickest path to the first piece of food
  AlgoResult result = run_algo(map, start, food_list, COUNT_OF(food_list), pathArray);

  // Event loop
  while (!WindowShouldClose()) {
    ClearBackground(BLACK);

    BeginDrawing();

    visualise_map(map, 20, 20);

    // Draw start and end points
    DrawCircle(T(start.x) + 20 + 5, T(start.y) + 20 + 5, 2, ORANGE);
    for (int i = 0; i < COUNT_OF(food_list); i++) {
      Point food = food_list[i];
      DrawCircle(T(food.x) + 20 + 5, T(food.y) + 20 + 5, 2, GREEN);
    }
    // Display path length
    char buffer[255];
    snprintf(buffer, sizeof(buffer), "Path Length: %ld", result.pathLength);
    DrawText(buffer, 20, 40 + T(MAP_HEIGHT), 15, WHITE);

    draw_path(pathArray, result.pathLength, 20, 20);

    EndDrawing();
  }
}

void visualise_map(uint8_t map[MAP_HEIGHT][MAP_WIDTH], int sx, int sy) {
  for (int y = 0; y < MAP_HEIGHT; y++) {
    for (int x = 0; x < MAP_WIDTH; x++) {
      if (map[y][x])
        DrawRectangle(T(x) + sx, T(y) + sy, GRID_SCALE, GRID_SCALE, WHITE);
      else
        DrawRectangleLines(T(x) + sx, T(y) + sy, GRID_SCALE, GRID_SCALE, WHITE);
    }
  }
}

void draw_path(Point *path, int pathLength, int sx, int sy) {

  Color drawColor;
  for (int i = 0; i < pathLength; i++) {
    Point curr = path[i];

    float percent = (((float)(i + 1)) / ((float)pathLength));
    drawColor = (Color){
        .a = 255,
        .r = (unsigned char)(255.0f * percent),
        .g = 0,
        .b = 255,
    };
    printf("Percent: %f\n", percent);

    DrawCircle(
        T(curr.x) + sx + GRID_SCALE / 2, T(curr.y) + sy + GRID_SCALE / 2, 3, drawColor);

    if (i < (pathLength - 1)) {
      Point next = path[i + 1];
      DrawLine(T(curr.x) + sx + GRID_SCALE / 2,
               T(curr.y) + sy + GRID_SCALE / 2,
               T(next.x) + sx + GRID_SCALE / 2,
               T(next.y) + sy + GRID_SCALE / 2,
               drawColor);
    }
  }
}

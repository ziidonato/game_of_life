#include "config.h"
#include "life/life.h"
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    uint8_t grid[GRID_SIZE][GRID_SIZE];
    memset(grid, 0, sizeof(grid));

    for (uint32_t x = 0; x < GRID_SIZE; x++) {
        for (uint32_t y = 0; y < GRID_SIZE; y++) {
            if ((x < (GRID_SIZE / 2) && y < (GRID_SIZE / 2)) ||
                (x >= (GRID_SIZE / 2) && y >= (GRID_SIZE / 2))) {
                grid[x][y] = 1;
            }
        }
    }

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (uint32_t x = 0; x < GRID_SIZE; x++) {
            for (uint32_t y = 0; y < GRID_SIZE; y++) {
                if (grid[x][y] == 1) {
                    DrawRectangle(x * 30 + 1, y * 30 + 1, 30 - 2, 30 - 2,
                                  BLACK);
                }
            }
        }
        EndDrawing();
    }

    // if (GENERATIONS > 0) {
    //     for (uint32_t i = 0; i < GENERATIONS; i++) {
    //         next_generation(grid);
    //     }
    // }
}

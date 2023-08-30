#include "config.h"
#include "life/life.h"
#include <pthread.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void *display_grid(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight,
               "raylib [core] example - basic window");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        pthread_mutex_lock(&grid_mutex);
        ClearBackground(RAYWHITE);
        for (uint32_t x = 0; x < GRID_SIZE; x++) {
            for (uint32_t y = 0; y < GRID_SIZE; y++) {
                if (grid[x][y] == 1) {
                    DrawRectangle(x * 30 + 1, y * 30 + 1, 30 - 2, 30 - 2,
                                  BLACK);
                }
            }
        }
        pthread_mutex_unlock(&grid_mutex);
        EndDrawing();
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1;
    pthread_create(&thread1, NULL, simulate, NULL);

    pthread_t thread2;
    pthread_create(&thread2, NULL, display_grid, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

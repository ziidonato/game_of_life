#include "gui.h"
#include "config.h"
#include "globals/globals.h"
#include <stdio.h>

#include <raylib.h>

void gui_init(void)
{
    InitWindow(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX, "Conway's Game of Life");
    SetTargetFPS(60);
}

void gui_draw_grid(struct grid_data *data, uint32_t cells_x, uint32_t cells_y)
{
    for (uint32_t x = 0; x < cells_x; x++) {
        for (uint32_t y = 0; y < cells_y; y++) {
            if (x + data->display_offset_x >= data->current_grid_size ||
                y + data->display_offset_y >= data->current_grid_size) {
                continue;
            }
            if (data->grid[x + data->display_offset_x]
                          [y + data->display_offset_y] == 1) {
                DrawRectangle(x * CELL_SIZE_PX + CELL_BORDER_PX,
                              y * CELL_SIZE_PX + CELL_BORDER_PX,
                              CELL_SIZE_PX - CELL_BORDER_PX * 2,
                              CELL_SIZE_PX - CELL_BORDER_PX * 2, BLACK);
            } else {
                DrawRectangle(x * CELL_SIZE_PX + CELL_BORDER_PX,
                              y * CELL_SIZE_PX + CELL_BORDER_PX,
                              CELL_SIZE_PX - CELL_BORDER_PX * 2,
                              CELL_SIZE_PX - CELL_BORDER_PX * 2, WHITE);
            }
        }
    }
}

void *gui_thread(void *_grid_data)
{
    struct grid_data *grid_data = _grid_data;

    gui_init();

    double generations_per_frame = GENERATIONS_PER_SECOND / 60.0;

    uint32_t cells_x = SCREEN_WIDTH_PX / CELL_SIZE_PX;
    uint32_t cells_y = SCREEN_HEIGHT_PX / CELL_SIZE_PX;

    while (!WindowShouldClose()) {
        if (generations_per_frame > 0) {
            pthread_mutex_lock(&grid_data->mutex);
            grid_data->generations_to_simulate += generations_per_frame;
            pthread_mutex_unlock(&grid_data->mutex);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        pthread_mutex_lock(&grid_data->mutex);
        gui_draw_grid(grid_data, cells_x, cells_y);
        pthread_mutex_unlock(&grid_data->mutex);
        DrawText("Generation: ", 10, 300, 20, BLACK);
        DrawText(TextFormat("%d", grid_data->current_generation), 150, 300, 20,
                 BLACK);
        EndDrawing();
    }

    pthread_mutex_lock(&grid_data->mutex);
    grid_data->exit_flag = 1;
    pthread_mutex_unlock(&grid_data->mutex);

    pthread_exit(NULL);
}

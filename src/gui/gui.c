#include "gui.h"
#include "base/types.h"
#include "life/sim.h"
#include <raylib.h>
#include <stdlib.h>

void gui_init(void)
{
    InitWindow(800, 450, "Game of Life");
    SetTargetFPS(60);
}

void gui_draw_grid(Array2D *array)
{
    for (uint64_t y = 0; y < array->height; y++) {
        for (uint64_t x = 0; x < array->width; x++) {
            Coord coord = {.x = x, .y = y};
            CellState state = array2d_get(array, coord);
            if (state == ALIVE) {
                DrawRectangle(x * 10, y * 10, 10, 10, BLACK);
            }
        }
    }
}

void gui_draw_hud(LifeSim *sim)
{
    const char *hud = TextFormat(
        "Generation: %lu / %lu",
        sim->current_generation,
        sim->total_generations_to_simulate
    );
    DrawText(hud, 10, 10, 20, BLACK);
}

void gui_draw(LifeSim *sim)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    gui_draw_grid(sim->array);
    gui_draw_hud(sim);
    EndDrawing();
}

void *gui_thread(void *arg)
{
    LifeSim *sim = (LifeSim *)arg;
    while (!WindowShouldClose()) {
        pthread_mutex_lock(&sim->mutex);
        gui_draw(sim);
        pthread_mutex_unlock(&sim->mutex);
    }
    return NULL;
}

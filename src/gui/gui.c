#include "gui.h"
#include "base/types.h"
#include "config.h"
#include "life/sim.h"
#include <raylib.h>
#include <stdlib.h>

void gui_init(void)
{
    InitWindow(SCREEN_WIDTH_PX, SCREEN_HEIGHT_PX, "Game of Life");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
}

void gui_draw_grid(Array2D *array)
{
    uint64_t width_squares = SCREEN_WIDTH_PX / CELL_SIZE_PX;
    uint64_t height_squares = SCREEN_HEIGHT_PX / CELL_SIZE_PX;
    for (uint64_t y = 0; y < array->height; y++) {
        for (uint64_t x = 0; x < array->width; x++) {
            Coord coord = {.x = x, .y = y};
            CellState state = array2d_get(array, coord);
            if (state == ALIVE) {
                DrawRectangle(
                    x * CELL_SIZE_PX + CELL_BORDER_PX,
                    y * CELL_SIZE_PX + CELL_BORDER_PX,
                    CELL_SIZE_PX - CELL_BORDER_PX,
                    CELL_SIZE_PX - CELL_BORDER_PX,
                    BLACK
                );
            } else {
                DrawRectangle(
                    x * CELL_SIZE_PX + CELL_BORDER_PX,
                    y * CELL_SIZE_PX + CELL_BORDER_PX,
                    CELL_SIZE_PX - CELL_BORDER_PX,
                    CELL_SIZE_PX - CELL_BORDER_PX,
                    WHITE
                );
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

    const char *hud2 = TextFormat(
        "Array Size: %lu x %lu",
        sim->array->height,
        sim->array->width
    );

    DrawRectangle(0, 0, MeasureText(hud, 20) + 20, 40, Fade(LIGHTGRAY, 0.5f));

    DrawText(hud, 10, 10, 20, BLACK);
    DrawText(hud2, 10, 30, 20, BLACK);
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
    LifeSimApplication *app = arg;
    LifeSim *sim = app->buffered_sim->display_sim;

    gui_init();
    while (!WindowShouldClose()) {
        pthread_mutex_lock(&sim->mutex);
        LifeSim *sim_copy = life_sim_copy(sim);
        pthread_mutex_unlock(&sim->mutex);

        gui_draw(sim_copy);
    }

    app->should_quit = 1;
    return NULL;
}

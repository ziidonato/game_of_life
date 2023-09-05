#include "base/base.h"
#include "config.h"
#include "globals/globals.h"
#include "gui/gui.h"
#include "life/life.h"
#include "life/patterns.h"
#include <pthread.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main()
{
    struct grid_data data = {
        .grid = init_grid(GRID_SIZE),
        .current_grid_size = GRID_SIZE,
        .total_generations_to_simulate = GENERATIONS,
        .generations_to_simulate = GENERATIONS < 0 ? -1 : 0,
        .exit_flag = 0,
        .current_generation = 0,
        .display_offset_x = 0,
        .display_offset_y = 0,
    };

    four_gliders(data.grid, data.current_grid_size);

    pthread_t thread1;
    pthread_create(&thread1, NULL, simulate, &data);

    pthread_t thread2;
    pthread_create(&thread2, NULL, gui_thread, &data);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

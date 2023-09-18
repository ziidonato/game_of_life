#include "config.h"
#include "gui/gui.h"
#include "life/sim.h"
#include <pthread.h>
#include <stdlib.h>

int main(void)
{
    LifeSim *sim = life_sim_new(GRID_SIZE, GRID_SIZE, GENERATIONS);

    for (int x = 0; x < sim->array->height; x++) {
        for (int y = 0; y < sim->array->width; y++) {
            // if in the top left or bottom right quadrant
            if ((x < sim->array->height / 2 && y < sim->array->width / 2)
                || (x >= sim->array->height / 2 && y >= sim->array->width / 2
                )) {
                Coord coord = {x, y};
                array2d_set(sim->array, coord, ALIVE);
            }
        }
    }

    BufferedSim *buffered_sim = buffered_sim_new(sim);

    LifeSimApplication life_sim_app = {
        .buffered_sim = buffered_sim,
        .should_quit = 0};

    pthread_t work_thread;
    pthread_t display_thread;

    pthread_create(&work_thread, NULL, simulate_thread, &life_sim_app);
    pthread_create(&display_thread, NULL, gui_thread, &life_sim_app);

    pthread_join(work_thread, NULL);
    pthread_join(display_thread, NULL);

    return 0;
}

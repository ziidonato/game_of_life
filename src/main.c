#include "gui/gui.h"
#include "life/sim.h"
#include <pthread.h>
#include <stdlib.h>

int main(void)
{
    LifeSim *sim = life_sim_new(45, 80, 1000);

    for (int x = 0; x < sim->array->height; x++) {
        for (int y = 0; y < sim->array->width; y++) {
            Coord coord = {x, y};
            array2d_set(sim->array, coord, ALIVE);
        }
    }

    BufferedSim *buffered_sim = buffered_sim_new(sim);

    pthread_t work_thread;
    pthread_t display_thread;

    pthread_create(&work_thread, NULL, simulate_thread, buffered_sim);
    pthread_create(
        &display_thread, NULL, gui_thread, buffered_sim->display_sim
    );

    pthread_join(work_thread, NULL);
    pthread_join(display_thread, NULL);

    return 0;
}

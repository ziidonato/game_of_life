#include "life/sim.h"
#include <pthread.h>
#include <stdlib.h>

int main(void)
{
    LifeSim *sim = malloc(sizeof(LifeSim));
    sim->current_generation = 0;
    sim->total_generations_to_simulate = 100;
    sim->array = array2d_new(10, 10);
    sim->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    for (uint64_t x = 0; x < sim->array->height; x++) {
        for (uint64_t y = 0; y < sim->array->width; y++) {
            Coord coord = {x, y};
            array2d_set(sim->array, coord, ALIVE);
        }
    }

    simulate(sim);

    array2d_print(sim->array);
    return 0;
}

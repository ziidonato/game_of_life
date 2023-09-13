#include "life/sim.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    LifeSim *sim = malloc(sizeof(LifeSim));
    sim->mutex = PTHREAD_MUTEX_INITIALIZER;
    sim->current_generation = 0;
    sim->total_generations_to_simulate = 100;
    sim->array = array2d_new(10, 10);

    for (size_t i = 0; i < sim->array->height; i++) {
        for (size_t j = 0; j < sim->array->width; j++) {
            Coord coord = {i, j};
            array2d_set(sim->array, coord, ALIVE);
        }
    }

    simulate(sim);
    array2d_print(sim->array);
}

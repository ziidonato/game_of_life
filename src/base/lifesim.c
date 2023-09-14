#include "types.h"
#include <stdlib.h>

LifeSim *life_sim_new(
    uint64_t height, uint64_t width, int64_t total_generations_to_simulate
)
{
    LifeSim *sim = malloc(sizeof(LifeSim));
    sim->current_generation = 0;
    sim->total_generations_to_simulate = total_generations_to_simulate;
    sim->array = array2d_new(height, width);
    sim->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

    return sim;
}

BufferedSim *buffered_sim_new(LifeSim *work_sim)
{
    BufferedSim *sim = malloc(sizeof(BufferedSim));
    LifeSim *display_sim = life_sim_new(
        work_sim->array->height,
        work_sim->array->width,
        work_sim->total_generations_to_simulate
    );

    array2d_copy(display_sim->array, work_sim->array);

    sim->work_sim = work_sim;
    sim->display_sim = display_sim;

    return sim;
}

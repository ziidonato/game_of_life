#include "base/base.h"
#include "globals/globals.h"
#include "life/life.h"
#include "life/patterns.h"
#include <pthread.h>
#include <ubench.h>

UBENCH_EX(four_gliders, 100_generations)
{
    struct grid_data data = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
    };

    UBENCH_DO_BENCHMARK()
    {
        data.current_generation = 0;
        data.grid = init_grid(100);
        data.current_grid_size = 100;
        data.total_generations_to_simulate = 100;
        data.generations_to_simulate = -1;
        four_gliders(data.grid, data.current_grid_size);
        simulate(&data);
    }
}

UBENCH_EX(two_squares, 100_generations)
{
    struct grid_data data = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
    };

    UBENCH_DO_BENCHMARK()
    {
        data.current_generation = 0;
        data.grid = init_grid(100);
        data.current_grid_size = 100;
        data.total_generations_to_simulate = 100;
        data.generations_to_simulate = -1;
        two_squares(data.grid, data.current_grid_size);
        simulate(&data);
    }
}

UBENCH_EX(four_gliders, 1000_generations)
{
    struct grid_data data = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
    };

    UBENCH_DO_BENCHMARK()
    {
        data.current_generation = 0;
        data.grid = init_grid(100);
        data.current_grid_size = 100;
        data.total_generations_to_simulate = 1000;
        data.generations_to_simulate = -1;
        four_gliders(data.grid, data.current_grid_size);
        simulate(&data);
    }
}

UBENCH_EX(two_squares, 1000_generations)
{
    struct grid_data data = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
    };

    UBENCH_DO_BENCHMARK()
    {
        data.current_generation = 0;
        data.grid = init_grid(100);
        data.current_grid_size = 100;
        data.total_generations_to_simulate = 1000;
        data.generations_to_simulate = -1;
        two_squares(data.grid, data.current_grid_size);
        simulate(&data);
    }
}

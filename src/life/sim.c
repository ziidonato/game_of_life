#include "sim.h"
#include "base/types.h"
#include <stdio.h>
#include <string.h>

uint8_t within_bounds(Array2D *array, Coord coord)
{
    return coord.x < array->width && coord.y < array->height;
}

CellState is_alive(Array2D *array, Coord coord)
{
    return within_bounds(array, coord) ? array2d_get(array, coord) == ALIVE
                                       : DEAD;
}

uint8_t neighbors(Array2D *array, Coord coord)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < 9; i++) {
        if (i == 4) {
            continue;
        }

        int64_t x_offset = i % 3 - 1;
        int64_t y_offset = i / 3 - 1;

        if (coord.x + x_offset < 0 || coord.y + y_offset < 0) {
            continue;
        }

        Coord new_coord = {coord.x + x_offset, coord.y + y_offset};

        if (is_alive(array, new_coord)) {
            count++;
        }
    }

    return count;
}

CellState next_state(Array2D *array, Coord coord)
{
    uint8_t count = neighbors(array, coord);
    uint8_t alive = is_alive(array, coord);

    return alive ? count == 2 || count == 3 : count == 3;
}

uint8_t lives_on_borders(Array2D *array)
{
    for (uint64_t x = 0; x < array->width; x++) {
        Coord bottom = {x, 0};
        Coord top = {x, array->height - 1};
        if (is_alive(array, bottom) || is_alive(array, top)) {
            return 1;
        }
    }

    for (uint64_t y = 0; y < array->height; y++) {
        Coord left = {0, y};
        Coord right = {array->width - 1, y};
        if (is_alive(array, left) || is_alive(array, right)) {
            return 1;
        }
    }

    return 0;
}

void next_generation(LifeSim *sim)
{

    if (lives_on_borders(sim->array)) {
        array2d_resize(
            sim->array,
            sim->array->height * 2,
            sim->array->width * 2
        );
    }

    Array2D *next = array2d_new(sim->array->height, sim->array->width);

    for (uint64_t x = 0; x < sim->array->height; x++) {
        for (uint64_t y = 0; y < sim->array->width; y++) {
            Coord coord = {x, y};
            CellState state = next_state(sim->array, coord);
            array2d_set(next, coord, state);
        }
    }

    array2d_free(sim->array);
    sim->array = next;
    sim->current_generation++;
}

uint8_t should_simulate(LifeSim *sim)
{
    return sim->current_generation < sim->total_generations_to_simulate;
}

uint8_t should_simulate_threaded(LifeSimApplication *app)
{
    return should_simulate(app->buffered_sim->work_sim) && !app->should_quit;
}

void simulate(LifeSim *sim)
{
    while (should_simulate(sim)) {
        next_generation(sim);
    }
}

void next_generation_threaded(LifeSim *sim)
{
    pthread_mutex_lock(&sim->mutex);
    next_generation(sim);
    pthread_mutex_unlock(&sim->mutex);
}

void change_buffer(BufferedSim *sim)
{
    LifeSim *work_sim = sim->work_sim;
    LifeSim *display_sim = sim->display_sim;
    Array2D *display_array = display_sim->array;
    Array2D *work_array = work_sim->array;

    if (pthread_mutex_trylock(&display_sim->mutex) != 0) {
        return;
    }

    pthread_mutex_lock(&work_sim->mutex);

    array2d_free(display_array);
    display_array = array2d_new(work_array->height, work_array->width);

    memcpy(
        display_array->data,
        work_array->data,
        work_array->height * work_array->width * sizeof(CellState)
    );

    display_sim->current_generation = work_sim->current_generation;
    pthread_mutex_unlock(&display_sim->mutex);
    pthread_mutex_unlock(&work_sim->mutex);
}

void *simulate_thread(void *arg)
{
    LifeSimApplication *app = arg;
    BufferedSim *sim = app->buffered_sim;

    pthread_mutex_lock(&sim->work_sim->mutex);
    while (should_simulate_threaded(app)) {
        pthread_mutex_unlock(&sim->work_sim->mutex);
        next_generation_threaded(sim->work_sim);

        change_buffer(sim);
    }

    pthread_mutex_unlock(&sim->work_sim->mutex);
    return NULL;
}

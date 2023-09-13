#include "sim.h"
#include "base/array2d.h"
#include "base/types.h"
#include <stdlib.h>

uint8_t within_bounds(Array2D *array, Coord coord)
{
    return coord.x < array->width && coord.y < array->height;
}

CellState is_alive(Array2D *array, Coord coord)
{
    return within_bounds(array, coord) && array2d_get(array, coord) == ALIVE;
}

uint8_t neighbors(Array2D *array, Coord coord)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < 9; i++) {
        if (i == 4) {
            continue;
        }

        if (i % 3 - 1 < 0 || i / 3 - 1 < 0) {
            continue;
        }

        uint64_t x_offset = i % 3 - 1;
        uint64_t y_offset = i / 3 - 1;

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
        array2d_resize(sim->array, sim->array->height * 2,
                       sim->array->width * 2);
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

void simulate(LifeSim *sim)
{
    while (sim->current_generation < sim->total_generations_to_simulate) {
        next_generation(sim);
    }
}

#pragma once
#include <pthread.h>
#include <stdint.h>

typedef enum CellState { DEAD = 0, ALIVE = 1 } CellState;

/// \brief a coordinate in a 2D array
typedef struct Coord {
    uint64_t x;
    uint64_t y;
} Coord;

/// \brief a 2D array of CellStates
typedef struct Array2D {
    uint64_t height;
    uint64_t width;
    CellState *data;
} Array2D;

Array2D *array2d_new(uint64_t height, uint64_t width);

CellState array2d_get(Array2D *array, Coord coord);

void array2d_set(Array2D *array, Coord coord, CellState state);

void array2d_resize(Array2D *array, uint64_t height, uint64_t width);

void array2d_free(Array2D *array);

void array2d_print(Array2D *array);

void array2d_copy(Array2D *dest, Array2D *src);

/// \brief a simulation of Conway's Game of Life
typedef struct LifeSim {
    Array2D *array;
    int64_t current_generation;
    int64_t total_generations_to_simulate;
    pthread_mutex_t mutex;

} LifeSim;

LifeSim *life_sim_new(
    uint64_t height, uint64_t width, int64_t total_generations_to_simulate
);

/// \brief a buffer of two LifeSims, one for work and one for display
typedef struct BufferedSim {
    LifeSim *work_sim;
    LifeSim *display_sim;
} BufferedSim;

BufferedSim *buffered_sim_new(LifeSim *work_sim);

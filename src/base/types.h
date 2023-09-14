#pragma once
#include <stdint.h>

typedef enum CellState { DEAD = 0, ALIVE = 1 } CellState;

typedef struct Coord {
    uint64_t x;
    uint64_t y;
} Coord;

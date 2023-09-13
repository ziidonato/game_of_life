#pragma once
#include <stdint.h>

typedef enum { DEAD = 0, ALIVE = 1 } CellState;

typedef struct {
    uint64_t x;
    uint64_t y;
} Coord;

#pragma once
#include "types.h"
#include <stdint.h>

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

#pragma once
#include <stddef.h>
#include <stdint.h>
#include "types.h"

typedef struct {
    size_t height;
    size_t width;
    CellState *data;
} Array2D;

Array2D *array2d_new(size_t height, size_t width);

CellState *array2d_get(Array2D *array, size_t row, size_t col);

void array2d_set(Array2D *array, size_t row, size_t col, CellState state);

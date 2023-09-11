#include "array2d.h"
#include <string.h>
#include <stdlib.h>

Array2D *array2d_new(size_t height, size_t width) {
    Array2D *array = malloc(sizeof(Array2D));
    array->height = height;
    array->width = width;
    array->data = malloc(height * width * sizeof(CellState));

    memset(array->data, 0, height * width * sizeof(CellState));
    return array;
}

CellState *array2d_get(Array2D *array, size_t row, size_t col) {
    return &array->data[row * array->width + col];
}

void array2d_set(Array2D *array, size_t row, size_t col, CellState state) {
    array->data[row * array->width + col] = state;
}

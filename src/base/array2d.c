#include "array2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Array2D *array2d_new(size_t height, size_t width)
{
    Array2D *array = malloc(sizeof(Array2D));
    array->height = height;
    array->width = width;
    array->data = malloc(height * width * sizeof(CellState));

    memset(array->data, 0, height * width * sizeof(CellState));
    return array;
}

CellState array2d_get(Array2D *array, Coord coord)
{
    return array->data[coord.x * array->width + coord.y];
}

void array2d_set(Array2D *array, Coord coord, CellState state)
{
    array->data[coord.x * array->width + coord.y] = state;
}

void array2d_resize(Array2D *array, uint64_t height, uint64_t width)
{

    CellState *temp = realloc(array->data, height * width * sizeof(CellState));
    if (temp == NULL) {
        free(array->data);
        array->data = NULL;
        exit(1);
    }

    array->data = temp;
    uint64_t offset = array->height / 2 * width + array->width / 2;

    memmove(array->data + offset, array->data,
            array->height * array->width * sizeof(CellState));
    memset(array->data, 0, offset * sizeof(CellState));

    array->height = height;
    array->width = width;
}

void array2d_free(Array2D *array)
{
    free(array->data);
    free(array);
}

void array2d_print(Array2D *array)
{
    for (uint64_t x = 0; x < array->height; x++) {
        for (uint64_t y = 0; y < array->width; y++) {
            Coord coord = {x, y};
            CellState state = array2d_get(array, coord);
            printf("%d ", state);
        }
        printf("\n");
    }

    printf("Height: %llu\n", array->height);
    printf("Width: %llu\n", array->width);
}

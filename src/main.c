#include "base/array2d.h"
#include <stdio.h>

int main(void) {
    Array2D *array = array2d_new(10, 10);

    for (size_t i = 0; i < array->height; i++) {
        for (size_t j = 0; j < array->width; j++) {
            array2d_set(array, i, j, ALIVE);
        }
    }
}

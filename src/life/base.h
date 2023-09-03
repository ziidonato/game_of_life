#pragma once
#include "config.h"
#include "globals/globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t **init_grid(uint32_t size)
{
    uint8_t **grid = malloc(sizeof(int *) * size);
    for (uint32_t i = 0; i < size; i++) {
        grid[i] = malloc(sizeof(uint8_t) * size);
        memset(grid[i], 0, sizeof(uint8_t) * size);
    }

    return grid;
}

void free_grid(uint8_t **grid, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++) {
        free(grid[i]);
    }
    free(grid);
}

void sleep_ms(uint32_t ms)
{
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
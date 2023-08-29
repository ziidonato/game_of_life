#include "../config.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t within_bounds(int32_t x, int32_t y)
{
    return x >= 0 && x < (int)GRID_SIZE && y >= 0 && y < (int)GRID_SIZE;
}

uint8_t is_neighbor(int32_t x, int32_t y, uint8_t grid[GRID_SIZE][GRID_SIZE])
{
    return within_bounds(x, y) && grid[x][y] == 1;
}

uint8_t neighbors(uint32_t x, uint32_t y, uint8_t grid[GRID_SIZE][GRID_SIZE])
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < 9; i++) {
        int32_t x_offset = i % 3 - 1;
        int32_t y_offset = i / 3 - 1;

        if (x_offset == 0 && y_offset == 0) {
            continue;
        }

        if (is_neighbor(x + x_offset, y + y_offset, grid)) {
            count++;
        }
    }

    return count;
}

uint8_t live_or_die(uint32_t value, uint8_t neighbors)
{
    uint8_t return_value = 0;

    if (value == 1) {
        if (neighbors < 2) {
            return_value = 0;
        } else if (neighbors > 3) {
            return_value = 0;
        } else {
            return_value = 1;
        }
    } else {
        if (neighbors == 3) {
            return_value = 1;
        } else {
            return_value = 0;
        }
    }

    return return_value;
}

void next_generation(uint8_t grid[GRID_SIZE][GRID_SIZE])
{
    uint8_t next_grid[GRID_SIZE][GRID_SIZE];
    memset(next_grid, 0, sizeof(next_grid));

    for (uint32_t x = 0; x < GRID_SIZE; x++) {
        for (uint32_t y = 0; y < GRID_SIZE; y++) {
            uint8_t neighbor_count = neighbors(x, y, grid);
            next_grid[x][y] = live_or_die(grid[x][y], neighbor_count);
        }
    }

    for (uint32_t x = 0; x < GRID_SIZE; x++) {
        for (uint32_t y = 0; y < GRID_SIZE; y++) {
            grid[x][y] = next_grid[x][y];
        }
    }
}
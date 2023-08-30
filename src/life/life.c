#include "life.h"
#include "../config.h"
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

uint8_t grid[GRID_SIZE][GRID_SIZE];
pthread_mutex_t grid_mutex;

void sleep_ms(uint32_t ms)
{
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

uint8_t within_bounds(int32_t x, int32_t y)
{
    return x >= 0 && x < (int)GRID_SIZE && y >= 0 && y < (int)GRID_SIZE;
}

uint8_t is_neighbor(int32_t x, int32_t y)
{
    return within_bounds(x, y) && grid[x][y] == 1;
}

uint8_t neighbors(uint32_t x, uint32_t y)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < 9; i++) {
        int32_t x_offset = i % 3 - 1;
        int32_t y_offset = i / 3 - 1;

        if (x_offset == 0 && y_offset == 0) {
            continue;
        }

        if (is_neighbor(x + x_offset, y + y_offset)) {
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

void next_generation()
{
    pthread_mutex_lock(&grid_mutex);
    uint8_t next_grid[GRID_SIZE][GRID_SIZE];
    memset(next_grid, 0, sizeof(next_grid));

    for (uint32_t x = 0; x < GRID_SIZE; x++) {
        for (uint32_t y = 0; y < GRID_SIZE; y++) {
            uint8_t neighbor_count = neighbors(x, y);
            next_grid[x][y] = live_or_die(grid[x][y], neighbor_count);
        }
    }

    for (uint32_t x = 0; x < GRID_SIZE; x++) {
        for (uint32_t y = 0; y < GRID_SIZE; y++) {
            grid[x][y] = next_grid[x][y];
        }
    }
    pthread_mutex_unlock(&grid_mutex);
}

void *simulate(void)
{
    int return_value = 0;
    if (pthread_mutex_init(&grid_mutex, NULL) != 0) {
        perror("Mutex init failed");
        return_value = 1;
    }

    pthread_mutex_lock(&grid_mutex);
    memset(grid, 0, sizeof(grid));

    for (uint32_t x = 0; x < GRID_SIZE; x++) {
        for (uint32_t y = 0; y < GRID_SIZE; y++) {
            if ((x < (GRID_SIZE / 2) && y < (GRID_SIZE / 2)) ||
                (x >= (GRID_SIZE / 2) && y >= (GRID_SIZE / 2))) {
                grid[x][y] = 1;
            }
        }
    }
    pthread_mutex_unlock(&grid_mutex);

    if (GENERATIONS == 0) {
        return_value = 0;
    }

    for (uint32_t i = 0; i < GENERATIONS; i++) {
        sleep_ms(SLEEP_TIME_MS);
        next_generation();
    }

    pthread_exit(&return_value);
}
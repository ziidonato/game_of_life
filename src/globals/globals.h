#pragma once
#include <pthread.h>
#include <stdint.h>

struct grid_data {
    uint8_t **grid;
    uint8_t exit_flag;
    pthread_mutex_t mutex;
    double generations_to_simulate;
    uint32_t current_grid_size;
    uint32_t current_generation;
    uint32_t display_offset_x;
    uint32_t display_offset_y;
};

void set_grid(struct grid_data *data, void (*pattern)(uint8_t **, uint32_t));
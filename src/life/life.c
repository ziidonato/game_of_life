#include "life.h"
#include "base.h"
#include "config.h"
#include "globals/globals.h"

uint8_t within_bounds(int32_t x, int32_t y, struct grid_data *data)
{
    return x >= 0 && x < (int)data->current_grid_size && y >= 0 &&
           y < (int)data->current_grid_size;
}

uint8_t is_neighbor(int32_t x, int32_t y, struct grid_data *data)
{
    return within_bounds(x, y, data) && data->grid[x][y] == 1;
}

uint8_t neighbors(uint32_t x, uint32_t y, struct grid_data *grid)
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

void expand_grid(struct grid_data *data)
{
    data->current_grid_size *= 2;
    uint8_t **new_grid = init_grid(data->current_grid_size);

    uint32_t offset = data->current_grid_size / 4;
    for (uint32_t x = 0; x < data->current_grid_size / 2; x++) {
        for (uint32_t y = 0; y < data->current_grid_size / 2; y++) {
            new_grid[x + offset][y + offset] = data->grid[x][y];
        }
    }

    free_grid(data->grid, data->current_grid_size / 2);
    data->grid = new_grid;

    data->display_offset_x += offset;
    data->display_offset_y += offset;
}

uint8_t lives_on_borders(struct grid_data *data)
{
    uint8_t return_value = 0;

    for (uint32_t x = 0; x < data->current_grid_size; x++) {
        if (x == 0 || x == data->current_grid_size - 1) {
            for (uint32_t y = 0; y < data->current_grid_size; y++) {
                if (data->grid[x][y] == 1) {
                    return_value = 1;
                    break;
                }
            }
        } else {
            if (data->grid[x][0] == 1 ||
                data->grid[x][data->current_grid_size - 1] == 1) {
                return_value = 1;
                break;
            }
        }
    }

    return return_value;
}

void next_generation(struct grid_data *data)
{
    pthread_mutex_lock(&data->mutex);

    if (lives_on_borders(data)) {
        expand_grid(data);
    }

    uint8_t next_grid[data->current_grid_size][data->current_grid_size];
    memset(next_grid, 0, sizeof(next_grid));

    for (uint32_t x = 0; x < data->current_grid_size; x++) {
        for (uint32_t y = 0; y < data->current_grid_size; y++) {
            uint8_t neighbor_count = neighbors(x, y, data);
            next_grid[x][y] = live_or_die(data->grid[x][y], neighbor_count);
        }
    }

    for (uint32_t x = 0; x < data->current_grid_size; x++) {
        for (uint32_t y = 0; y < data->current_grid_size; y++) {
            data->grid[x][y] = next_grid[x][y];
        }
    }

    data->current_generation++;
    data->generations_to_simulate--;
    pthread_mutex_unlock(&data->mutex);
}

void *simulate(void *grid_data)
{
    struct grid_data *data = (struct grid_data *)grid_data;
    int return_value = 0;

    pthread_mutex_lock(&data->mutex);
    data->grid = init_grid(data->current_grid_size);

    for (uint32_t x = 0; x < data->current_grid_size; x++) {
        for (uint32_t y = 0; y < data->current_grid_size; y++) {
            if (x <= data->current_grid_size / 2 &&
                    y >= data->current_grid_size / 2 ||
                x >= data->current_grid_size / 2 &&
                    y <= data->current_grid_size / 2) {
                data->grid[x][y] = 1;
            }
        }
    }

    pthread_mutex_unlock(&data->mutex);

    if (GENERATIONS == 0) {
        return_value = 0;
    }

    while (data->current_generation < GENERATIONS || GENERATIONS < 0) {
        pthread_mutex_lock(&data->mutex);
        if (data->exit_flag == 1) {
            pthread_mutex_unlock(&data->mutex);
            return_value = 0;
            break;
        }
        pthread_mutex_unlock(&data->mutex);

        while (data->generations_to_simulate >= 1.0) {
            next_generation(data);
        }

        if (data->generations_to_simulate < 0) {
            next_generation(data);
        }
    }

    pthread_exit(&return_value);
}

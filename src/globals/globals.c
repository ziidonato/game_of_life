#include "globals.h"

void set_grid(struct grid_data *data, void (*pattern)(uint8_t **, uint32_t))
{
    pthread_mutex_lock(&data->mutex);
    pattern(data->grid, data->current_grid_size);
    pthread_mutex_unlock(&data->mutex);
}

#pragma once
#include "globals/globals.h"
int simulate(struct grid_data *grid_data);
void *simulate_thread(void *grid_data);

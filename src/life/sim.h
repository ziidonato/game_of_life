#pragma once
#include "base/array2d.h"

typedef struct {
    Array2D *array;
    int64_t current_generation;
    int64_t total_generations_to_simulate;
} LifeSim;

void simulate(LifeSim *sim);
void *simulate_thread(void *arg);
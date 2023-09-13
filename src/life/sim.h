#pragma once
#include "base/array2d.h"
#include <pthread.h>

typedef struct {
    Array2D *array;
    int64_t current_generation;
    int64_t total_generations_to_simulate;
    pthread_mutex_t mutex;

} LifeSim;

typedef struct {
    LifeSim *work_sim;
    LifeSim *display_sim;
} BufferedSim;

void simulate(LifeSim *sim);
void *simulate_thread(void *arg);

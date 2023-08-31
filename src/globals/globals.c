#include "config.h"
#include <pthread.h>
#include <stdint.h>

const pthread_cond_t worker_cond = PTHREAD_COND_INITIALIZER;

uint8_t grid[GRID_SIZE][GRID_SIZE];
pthread_mutex_t grid_mutex = PTHREAD_MUTEX_INITIALIZER;
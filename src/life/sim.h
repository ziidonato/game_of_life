#pragma once
#include "base/types.h"
#include <pthread.h>

void simulate(LifeSim *sim);
void *simulate_thread(void *arg);

#pragma once
#include "../config.h"
#include <stdint.h>

extern const uint8_t grid[GRID_SIZE][GRID_SIZE];
uint8_t within_bounds(int32_t x, int32_t y);
uint8_t is_neighbor(uint32_t x, uint32_t y, uint8_t grid[GRID_SIZE][GRID_SIZE]);
uint8_t neighbors(uint32_t x, uint32_t y, uint8_t grid[GRID_SIZE][GRID_SIZE]);
uint8_t live_or_die(uint32_t value, uint8_t neighbors);
void next_generation(uint8_t grid[GRID_SIZE][GRID_SIZE]);
#pragma once
#include "config.h"
#include "globals/globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t **init_grid(uint32_t size);

void free_grid(uint8_t **grid, uint32_t size);

void sleep_ms(uint32_t ms);

struct ordered_pair {
    uint32_t x;
    uint32_t y;
};
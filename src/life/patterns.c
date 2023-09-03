#include "patterns.h"
#include "base/base.h"

void up_left_glider(struct ordered_pair *pair, uint8_t **grid)
{
    grid[pair->x][pair->y] = 1;
    grid[pair->x + 1][pair->y] = 1;
    grid[pair->x + 2][pair->y] = 1;
    grid[pair->x + 2][pair->y + 1] = 1;
    grid[pair->x + 1][pair->y + 2] = 1;
}

void up_right_glider(struct ordered_pair *pair, uint8_t **grid)
{
    grid[pair->x][pair->y] = 1;
    grid[pair->x + 1][pair->y] = 1;
    grid[pair->x + 2][pair->y] = 1;
    grid[pair->x][pair->y + 1] = 1;
    grid[pair->x + 1][pair->y + 2] = 1;
}

void down_left_glider(struct ordered_pair *pair, uint8_t **grid)
{
    grid[pair->x][pair->y] = 1;
    grid[pair->x + 1][pair->y] = 1;
    grid[pair->x + 2][pair->y] = 1;
    grid[pair->x + 2][pair->y - 1] = 1;
    grid[pair->x + 1][pair->y - 2] = 1;
}

void down_right_glider(struct ordered_pair *pair, uint8_t **grid)
{
    grid[pair->x][pair->y] = 1;
    grid[pair->x + 1][pair->y] = 1;
    grid[pair->x + 2][pair->y] = 1;
    grid[pair->x][pair->y - 1] = 1;
    grid[pair->x + 1][pair->y - 2] = 1;
}

void four_gliders(uint8_t **grid, uint32_t size)
{
    struct ordered_pair upper_left_pair = {
        .x = size / 4,
        .y = size / 4,
    };

    struct ordered_pair upper_right_pair = {
        .x = size / 4 * 3,
        .y = size / 4,
    };

    struct ordered_pair lower_left_pair = {
        .x = size / 4,
        .y = size / 4 * 3,
    };

    struct ordered_pair lower_right_pair = {
        .x = size / 4 * 3,
        .y = size / 4 * 3,
    };

    up_left_glider(&upper_left_pair, grid);
    up_right_glider(&upper_right_pair, grid);
    down_left_glider(&lower_left_pair, grid);
    down_right_glider(&lower_right_pair, grid);
}

void two_squares(uint8_t **grid, uint32_t size)
{
    for (uint32_t x = 0; x < size; x++) {
        for (uint32_t y = 0; y < size; y++) {
            if ((x < size / 2 - 1 && y < size / 2 - 1) ||
                (x >= size / 2 - 1 && y >= size / 2 - 1)) {
                grid[x][y] = 1;
            }
        }
    }
}
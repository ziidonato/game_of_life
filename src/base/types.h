#pragma once
#include <pthread.h>
#include <stdint.h>

/// \brief a cell's state
/// \note DEAD = 0, ALIVE = 1
typedef enum CellState { DEAD = 0, ALIVE = 1 } CellState;

/// \brief a coordinate in a 2D array
typedef struct Coord {
    /// \brief the x coordinate
    uint64_t x;

    /// \brief the y coordinate
    uint64_t y;
} Coord;

/// \brief a 2D array of CellStates
typedef struct Array2D {
    /// \brief the height of the array
    uint64_t height;

    /// \brief the width of the array
    uint64_t width;

    /// \brief the array of CellStates
    CellState *data;
} Array2D;

/// \brief creates a new Array2D
/// \param height the height of the array
/// \param width the width of the array
Array2D *array2d_new(uint64_t height, uint64_t width);

/// \brief gets a CellState from an Array2D
/// \param array the Array2D to get the CellState from
CellState array2d_get(Array2D *array, Coord coord);

/// \brief sets a CellState in an Array2D
/// \param array the Array2D to set the CellState in
void array2d_set(Array2D *array, Coord coord, CellState state);

/// \brief resizes an Array2D
/// \param array the Array2D to resize
/// \param height the new height of the Array2D
void array2d_resize(Array2D *array, uint64_t height, uint64_t width);

/// \brief frees an Array2D
/// \param array the Array2D to free
void array2d_free(Array2D *array);

/// \brief prints an Array2D
/// \param array the Array2D to print
void array2d_print(Array2D *array);

/// \brief copies an Array2D
/// \param dest the Array2D to copy to
/// \param src the Array2D to copy from
void array2d_copy(Array2D *dest, Array2D *src);

/// \brief a simulation of Conway's Game of Life
typedef struct LifeSim {
    /// \brief the array of CellStates
    Array2D *array;

    /// \brief the current generation
    int64_t current_generation;

    /// \brief the total number of generations to simulate
    int64_t total_generations_to_simulate;

    /// \brief a mutex to lock the LifeSim
    pthread_mutex_t mutex;

} LifeSim;

/// \brief creates a new LifeSim
/// \param height the height of the LifeSim's array
/// \param width the width of the LifeSim's array
/// \param total_generations_to_simulate the number of generations to simulate
LifeSim *life_sim_new(
    uint64_t height,
    uint64_t width,
    int64_t total_generations_to_simulate
);

/// \brief copies a LifeSim, including its array
/// \note used when passing a LifeSim to the GUI thread
/// \param sim the LifeSim to copy
LifeSim *life_sim_copy(LifeSim *sim);

/// \brief a buffer of two LifeSims, one for work and one for display
typedef struct BufferedSim {
    /// \brief the LifeSim to use for work
    LifeSim *work_sim;
    /// \brief the LifeSim to use for display
    LifeSim *display_sim;
} BufferedSim;

/// \brief creates a new BufferedSim
/// \param work_sim the LifeSim to use for work
BufferedSim *buffered_sim_new(LifeSim *work_sim);

typedef struct LifeSimApplication {
    uint8_t should_quit;
    BufferedSim *buffered_sim;
} LifeSimApplication;

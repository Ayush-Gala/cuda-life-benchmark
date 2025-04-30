#ifndef SAMPLE_POOLS_H
#define SAMPLE_POOLS_H

// Function prototypes for pool initialization
void initialize_glider(int* grid, int grid_width, int grid_height, int start_row, int start_col);
void initialize_glider_gun(int* grid, int grid_width, int grid_height, int start_row, int start_col);
void initialize_demonoid(int* grid, int grid_width, int grid_height, int start_row, int start_col);
void initialize_random_grid(int* grid, int grid_width, int grid_height, float density);
void clear_grid(int* grid, int grid_width, int grid_height);

#endif // SAMPLE_POOLS_H
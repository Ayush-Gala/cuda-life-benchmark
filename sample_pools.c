#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sample_pools.h"

// Function to clear the grid (set all cells to dead)
void clear_grid(int* grid, int grid_width, int grid_height) {
    for (int i = 0; i < grid_height * grid_width; i++) {
        grid[i] = 0;
    }
}

// Function to initialize a random grid with specified density of live cells
void initialize_random_grid(int* grid, int grid_width, int grid_height, float density) {
    // Seed the random number generator if not already done
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    // Clear the grid first
    clear_grid(grid, grid_width, grid_height);
    
    // Set random cells to alive based on density (0.0 to 1.0)
    for (int i = 0; i < grid_height; i++) {
        for (int j = 0; j < grid_width; j++) {
            if ((float)rand() / RAND_MAX < density) {
                grid[i * grid_width + j] = 1;
            }
        }
    }
}

// Helper function to safely set a cell value with boundary checking
static void set_cell(int* grid, int grid_width, int grid_height, int row, int col, int value) {
    if (row >= 0 && row < grid_height && col >= 0 && col < grid_width) {
        grid[row * grid_width + col] = value;
    }
}

// Initialize a single glider pattern at the specified position
void initialize_glider(int* grid, int grid_width, int grid_height, int start_row, int start_col) {
    // Clear the grid first
    clear_grid(grid, grid_width, grid_height);
    
    // Set glider pattern (classic "northwest" moving glider)
    set_cell(grid, grid_width, grid_height, start_row,   start_col+1, 1);
    set_cell(grid, grid_width, grid_height, start_row+1, start_col+2, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col,   1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+1, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+2, 1);
}

// Initialize a Gosper Glider Gun pattern at the specified position
void initialize_glider_gun(int* grid, int grid_width, int grid_height, int start_row, int start_col) {
    // Clear the grid first
    clear_grid(grid, grid_width, grid_height);
    
    // Left block
    set_cell(grid, grid_width, grid_height, start_row+4, start_col+0, 1);
    set_cell(grid, grid_width, grid_height, start_row+4, start_col+1, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+0, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+1, 1);

    // Left ship
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+12, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+13, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+11, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+15, 1);
    set_cell(grid, grid_width, grid_height, start_row+4, start_col+10, 1);
    set_cell(grid, grid_width, grid_height, start_row+4, start_col+16, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+10, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+14, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+16, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+17, 1);
    set_cell(grid, grid_width, grid_height, start_row+6, start_col+10, 1);
    set_cell(grid, grid_width, grid_height, start_row+6, start_col+16, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+11, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+15, 1);
    set_cell(grid, grid_width, grid_height, start_row+8, start_col+12, 1);
    set_cell(grid, grid_width, grid_height, start_row+8, start_col+13, 1);

    // Right block
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+20, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+21, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+20, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+21, 1);

    // Right ship
    set_cell(grid, grid_width, grid_height, start_row+0, start_col+34, 1);
    set_cell(grid, grid_width, grid_height, start_row+1, start_col+32, 1);
    set_cell(grid, grid_width, grid_height, start_row+1, start_col+34, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+22, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+23, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+30, 1);
    set_cell(grid, grid_width, grid_height, start_row+2, start_col+31, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+22, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+23, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+30, 1);
    set_cell(grid, grid_width, grid_height, start_row+3, start_col+31, 1);
    set_cell(grid, grid_width, grid_height, start_row+4, start_col+24, 1);
    set_cell(grid, grid_width, grid_height, start_row+4, start_col+28, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+24, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+26, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+28, 1);
    set_cell(grid, grid_width, grid_height, start_row+5, start_col+29, 1);
    set_cell(grid, grid_width, grid_height, start_row+6, start_col+24, 1);
    set_cell(grid, grid_width, grid_height, start_row+6, start_col+28, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+25, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+26, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+27, 1);
}

// Initialize 0hd Demonoid pattern at the specified position
void initialize_demonoid(int* grid, int grid_width, int grid_height, int start_row, int start_col) {
    // Clear the grid first
    clear_grid(grid, grid_width, grid_height);
    
    // 0hd Demonoid pattern (a relatively large pattern that exhibits complex behavior)
    // This is a simplified version of the pattern
    
    // Center structure
    set_cell(grid, grid_width, grid_height, start_row+10, start_col+10, 1);
    set_cell(grid, grid_width, grid_height, start_row+10, start_col+11, 1);
    set_cell(grid, grid_width, grid_height, start_row+10, start_col+12, 1);
    set_cell(grid, grid_width, grid_height, start_row+11, start_col+9, 1);
    set_cell(grid, grid_width, grid_height, start_row+11, start_col+13, 1);
    set_cell(grid, grid_width, grid_height, start_row+12, start_col+9, 1);
    set_cell(grid, grid_width, grid_height, start_row+12, start_col+13, 1);
    set_cell(grid, grid_width, grid_height, start_row+13, start_col+10, 1);
    set_cell(grid, grid_width, grid_height, start_row+13, start_col+11, 1);
    set_cell(grid, grid_width, grid_height, start_row+13, start_col+12, 1);
    
    // Wings
    set_cell(grid, grid_width, grid_height, start_row+8, start_col+14, 1);
    set_cell(grid, grid_width, grid_height, start_row+8, start_col+15, 1);
    set_cell(grid, grid_width, grid_height, start_row+9, start_col+14, 1);
    set_cell(grid, grid_width, grid_height, start_row+14, start_col+7, 1);
    set_cell(grid, grid_width, grid_height, start_row+14, start_col+8, 1);
    set_cell(grid, grid_width, grid_height, start_row+15, start_col+8, 1);
    
    // Spaceship components
    set_cell(grid, grid_width, grid_height, start_row+6, start_col+17, 1);
    set_cell(grid, grid_width, grid_height, start_row+6, start_col+18, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+16, 1);
    set_cell(grid, grid_width, grid_height, start_row+7, start_col+19, 1);
    set_cell(grid, grid_width, grid_height, start_row+8, start_col+19, 1);
    
    set_cell(grid, grid_width, grid_height, start_row+16, start_col+5, 1);
    set_cell(grid, grid_width, grid_height, start_row+17, start_col+4, 1);
    set_cell(grid, grid_width, grid_height, start_row+17, start_col+5, 1);
    set_cell(grid, grid_width, grid_height, start_row+17, start_col+6, 1);
    set_cell(grid, grid_width, grid_height, start_row+18, start_col+5, 1);
}
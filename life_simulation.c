#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>    // For timing functionality
#include "sample_pools.h"

// Constants for grid dimensions
#define GRID_H 1000
#define GRID_W 1000
#define NUM_ITERATIONS 557

static int evaluate_cell(int i, int j, int* grid);
void print_grid(int* grid);

// Run the simulation for a specified number of iterations
void run_simulation(int* grid) {
    int* updated_grid;
    int* temp;
    bool grid_change = true;
    clock_t start_time, end_time;
    double total_time = 0.0;
    
    updated_grid = (int*)malloc(sizeof(int) * GRID_H * GRID_W);

    // Start timer for this iteration
    start_time = clock();
    
    for (int iteration = 0; iteration < NUM_ITERATIONS && grid_change; iteration++) {
        grid_change = false;
        
        // Compute the next generation
        for (int i = 0; i < GRID_H; i++) {
            for (int j = 0; j < GRID_W; j++) {
                int index = i * GRID_W + j;
                updated_grid[index] = evaluate_cell(i, j, grid);
                if (updated_grid[index] != grid[index]) {
                    grid_change = true;
                }
            }
        }
        
        // Swap grids
        temp = updated_grid;
        updated_grid = grid;
        grid = temp;
        
        printf("Iteration %d complete\n", iteration + 1);
        
        // Optional: print grid at each step for debugging
        // print_grid(grid);
    }

    end_time = clock();
    total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\nTotal computation time: %.6f seconds\n", total_time);
    printf("Average time per iteration: %.6f seconds\n", total_time / NUM_ITERATIONS);
    
    free(updated_grid);
}

// Evaluate the state of a cell for the next generation
static int evaluate_cell(int i, int j, int* grid) {
    int alive_cells = 0;
    
    // Count living neighbors
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            // Skip the cell itself
            if (di == 0 && dj == 0) continue;
            
            int ni = i + di;
            int nj = j + dj;
            
            // Check boundaries
            if (ni >= 0 && ni < GRID_H && nj >= 0 && nj < GRID_W) {
                alive_cells += grid[ni * GRID_W + nj];
            }
        }
    }
    
    // Apply Conway's Game of Life rules
    if (grid[i * GRID_W + j]) {
        // Cell is alive
        return (alive_cells == 2 || alive_cells == 3) ? 1 : 0;
    } else {
        // Cell is dead
        return (alive_cells == 3) ? 1 : 0;
    }
}

// Utility function to print the grid (for debugging)
void print_grid(int* grid) {
    // For large grids, only print a corner sample
    int sample_size = 20;
    int display_size = (GRID_H > sample_size) ? sample_size : GRID_H;
    
    printf("Grid sample (top-left %dx%d):\n", display_size, display_size);
    for (int i = 0; i < display_size; i++) {
        for (int j = 0; j < display_size; j++) {
            printf("%c ", grid[i * GRID_W + j] ? '#' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int* grid = (int*)malloc(sizeof(int) * GRID_H * GRID_W);
    clock_t total_start, total_end;
    double initialization_time, simulation_time, total_program_time;
    int pattern_choice;
    
    printf("Conway's Game of Life Performance Benchmark\n");
    printf("Grid size: %d x %d (%d cells)\n", GRID_H, GRID_W, GRID_H * GRID_W);
    printf("Max iterations: %d\n\n", NUM_ITERATIONS);
    
    // Ask user which pattern to use
    printf("Select initial pattern:\n");
    printf("1: Random grid\n");
    printf("2: Single glider\n");
    printf("3: Gosper glider gun\n");
    printf("4: 0hd Demonoid\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &pattern_choice);
    
    // Start total program timer
    total_start = clock();
    
    // Time the initialization
    clock_t init_start = clock();
    
    // Initialize grid with chosen pattern
    switch(pattern_choice) {
        case 1:
            printf("Initializing random grid (50%% density)...\n");
            initialize_random_grid(grid, GRID_W, GRID_H, 0.5);
            break;
        case 2:
            printf("Initializing single glider...\n");
            initialize_glider(grid, GRID_W, GRID_H, GRID_H/2, GRID_W/2);
            break;
        case 3:
            printf("Initializing Gosper glider gun...\n");
            initialize_glider_gun(grid, GRID_W, GRID_H, GRID_H/2, GRID_W/2);
            break;
        case 4:
            printf("Initializing 0hd Demonoid...\n");
            initialize_demonoid(grid, GRID_W, GRID_H, GRID_H/2, GRID_W/2);
            break;
        default:
            printf("Invalid choice, using random grid...\n");
            initialize_random_grid(grid, GRID_W, GRID_H, 0.5);
    }
    
    clock_t init_end = clock();
    initialization_time = ((double) (init_end - init_start)) / CLOCKS_PER_SEC;
    printf("Grid initialization time: %.6f seconds\n\n", initialization_time);
    
    // Modified print_grid to only show a sample for large grids
    // print_grid(grid);
    
    // Time the simulation
    clock_t sim_start = clock();
    run_simulation(grid);
    clock_t sim_end = clock();
    simulation_time = ((double) (sim_end - sim_start)) / CLOCKS_PER_SEC;
    
    // End total program timer
    total_end = clock();
    total_program_time = ((double) (total_end - total_start)) / CLOCKS_PER_SEC;
    
    // Print timing summary
    printf("\nTIMING SUMMARY:\n");
    printf("Initialization time: %.6f seconds\n", initialization_time);
    printf("Simulation time:     %.6f seconds\n", simulation_time);
    printf("Total program time:  %.6f seconds\n", total_program_time);
    
    // Print final state (sample)
    print_grid(grid);
    
    // Clean up
    free(grid);
    
    return 0;
}
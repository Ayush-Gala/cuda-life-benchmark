# cuda-life-benchmark

*A high-performance, parallelized simulation and benchmarking suite for Conway’s Game of Life using CUDA and OpenMP, designed to explore and compare the computational efficiency of modern CPUs and GPUs for cellular automata research.*

---

## 🧬 Introduction

Conway's Game of Life (GoL), invented by John Conway in 1970, is a classic cellular automaton that demonstrates how simple local rules can generate complex, emergent behaviors. The game consists of a two-dimensional grid of cells, each of which can be either **alive** or **dead**.

The evolution of the grid is determined by the following rules:

- Any live cell with **two or three live neighbors** survives.
- Any dead cell with **exactly three live neighbors** becomes alive.
- All other live cells die, and dead cells remain dead.

Despite its simplicity, GoL produces a rich variety of patterns—ranging from stable structures and oscillators to self-replicating machines and chaotic behavior—making it a benchmark problem in parallel algorithm research.

---

## 📌 Problem Definition

Simulating GoL at scale is **computationally intensive**, especially for large grids and many generations. Each cell's state update requires reading its eight neighbors, making this a **memory-bound** rather than compute-bound problem.

This project targets the efficient simulation of a **1000 × 1000** grid over **557 generations**, using the **"0hd Demonoid"** pattern as a reproducible benchmark. The challenge lies in **maximizing parallel throughput** while **minimizing memory bottlenecks** on modern hardware.

---

## ⚙️ Overview of Implementations

### 🔹 Serial Implementation

- Uses a double-buffering approach with two 2D arrays.
- For each generation:
  - Compute each cell's next state based on the Moore neighborhood.
  - Enforce toroidal boundary conditions using ghost cells.
- Pointer swapping avoids costly data copying.
- Timing excludes initialization and focuses on pure computation.

---

### 🔹 OpenMP Implementation

- Introduces shared-memory parallelism:
  - Parallelized with `#pragma omp parallel for schedule(dynamic) collapse(2)`.
- Dynamic scheduling balances workload across CPU cores.
- Limited speedup due to memory bandwidth bottleneck:
  - **Speedup (16 threads):** `1.46×`

---

### 🔹 CUDA Implementation

- Leverages GPU parallelism:
  - Grid flattened to 1D for coalesced memory access.
  - Double-buffering on device to avoid hazards.
  - 2D kernel grid: each thread updates one cell.
- Boundary handling via ghost cells prevents warp divergence.

#### ✅ Optimizations:
- Branchless logic to reduce divergence.
- Pinned host memory for fast transfers.
- CUDA streams to overlap compute and transfers.
- Shared memory caching and coalesced accesses.

> **Final Speedup:** `111×` over serial  
> **Parallel Efficiency:** `86.4%`

---

## 🧱 Data Structures and Boundary Handling

| Feature              | CPU                     | GPU                     |
|----------------------|--------------------------|--------------------------|
| Grid Representation  | 2D array                 | Flattened 1D array       |
| Cell State           | `1 = alive`, `0 = dead` | Same                     |
| Boundary Conditions  | Toroidal via ghost cells | Same                     |
| Buffering            | Double-buffered          | Double-buffered          |

---

## 📊 Benchmarking and Results

**Test Pattern:** `"0hd Demonoid"` (Class VI, complex and reproducible)  
**Grid Size:** `1000 × 1000`  
**Generations:** `557`  
**Hardware:** ARC NCSU supercluster with Intel AEP 3DXP, NVIDIA A100 GPU

| Implementation     | Time (s) | Speedup | Efficiency |
|--------------------|---------:|--------:|-----------:|
| Serial             | 100.0    | 1.00×   | 100.0%     |
| OpenMP (16 threads)| 68.4     | 1.46×   | 9.1%       |
| CUDA Baseline      | 4.3      | 23.26×  | 72.7%      |
| CUDA Optimized     | 0.9      | 111.11× | 86.4%      |

**Notes:**
- OpenMP limited by memory bandwidth.
- CUDA Baseline benefits from massive parallelism.
- CUDA Optimized maximizes memory and execution efficiency.

---

## 🛠️ How to Build and Run the Serial Implementation

The repository includes a `Makefile` for easy compilation and execution.

### 🔧 Prerequisites
- GCC (GNU Compiler Collection)
- `make` utility

### 📄 Makefile Overview

```makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra

# Output executable
TARGET = life_sim

# Source files
SRCS = life_simulation.c sample_pools.c

# Default target: compile the program
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up build artifacts
clean:
	rm -f $(TARGET)
```

### 🚀 Build Steps

1. Clone the repository

```sh
git clone https://github.com/Ayush-Gala/cuda-life-benchmark.git
cd cuda-life-benchmark
```

2. Compile the serial implementation

```sh
make
```

3. Run the program
```sh
make run
```
Gives the user choice for setting the starting pool. Future support for more pools is coming soon. Select 0hd demonoid to simulate the benchmark.

4. Clean build artifacts
```sh
make clean
```

---
## 🛠️ How to Build and Run the CUDA Implementation

This section provides a step-by-step guide to setting up, building, and running the CUDA-accelerated version of Conway's Game of Life on an NVIDIA A100 GPU. 

### Software Prerequisites and Dependencies

Before proceeding, ensure your system meets the following requirements:
- NVIDIA A100 GPU (Ampere architecture)
- CUDA Toolkit: Version 11.4 or later is required for A100 GPUs.
- NVIDIA Driver: R450 or newer is required for A100 GPUs.
- gcc/g++: Standard C/C++ compilers for host code.
- SDL2 Development Libraries: For visualization support (libsdl2-dev on Ubuntu).
- Linux OS: Preferably Ubuntu 20.04+ or CentOS 8+ for best compatibility.

### Install Dependencies (Ubuntu Example)

```sh
# Install NVIDIA driver and CUDA Toolkit (if not already installed)
# Follow official NVIDIA documentation for your OS and hardware

# Install build tools and SDL2
sudo apt-get update
sudo apt-get install -y build-essential libsdl2-dev
```

### Project Directory Structure

```text
cuda-life-benchmark/
├── allocate_grid.c
├── draw_grid.c
├── get_run_mode.c
├── run_simulation.c
├── init_world.c
├── scene_update.c
├── run_simulation_cuda.cu
├── main.cu
├── ... (other files)
```

### Step-by-Step Build Instructions

1. Clone the Repository

```sh
git clone https://github.com/Ayush-Gala/cuda-life-benchmark.git
cd cuda-life-benchmark
```

2. Compile All Source Files
The CUDA implementation uses both .c and .cu files. The main compiler is nvcc, which can compile both CUDA and standard C files.

```sh
# Compile all C and CUDA source files into object files
nvcc -I SDL2 -c allocate_grid.c
nvcc -I SDL2 -c draw_grid.c
nvcc -I SDL2 -c get_run_mode.c
nvcc -I SDL2 -c run_simulation.c
nvcc -I SDL2 -c init_world.c
nvcc -I SDL2 -c scene_update.c
nvcc -I SDL2 -c run_simulation_cuda.cu
nvcc -I SDL2 -c main.cu
```

3. Link Object Files into Executable

```sh
nvcc -I SDL2 -o grid allocate_grid.o draw_grid.o get_run_mode.o run_simulation.o init_world.o scene_update.o run_simulation_cuda.o main.o -lSDL2
```

4.  Run the CUDA Program
```sh
./grid
```

This will launch the CUDA-accelerated simulation. If SDL2 support is enabled and compiled, a visualization window may appear.

5. Optional: Profiling with NVIDIA Nsight Systems
If you wish to profile the CUDA execution:

```sh
# Replace the path with your actual Nsight Systems installation if needed
~/nsight-systems-2021.2.1/bin/nsys profile ./grid
```

## Notes and Troubleshooting

- Ensure your CUDA Toolkit and driver versions are compatible with the A100 GPU (CUDA 11.4+ and R450+ driver).
- If you encounter missing SDL2 headers or libraries, double-check the installation (libsdl2-dev).
- For headless servers, you may need to disable or bypass SDL2 visualization features.
- The actual file names may differ; adjust the commands if your source files have different names or locations.

## 🚀 Future Directions

- Extended Benchmark Suite: Vary grid sizes, density, and boundary conditions.
- Visualization: Integrate OpenGL for real-time feedback.
- Adaptive Runtime: Implement dynamic load balancing and hybrid CPU-GPU scheduling.

## ✅ Conclusion

This project shows that with careful parallelization and architectural tuning, cellular automata like Conway’s Game of Life can achieve orders-of-magnitude performance gains. This project serves as a robust platform for benchmarking, parallel research, and exploring advanced optimizations in scientific computing.

# Contributors

- Ayush Gala (agala2@ncsu.edu)

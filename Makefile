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

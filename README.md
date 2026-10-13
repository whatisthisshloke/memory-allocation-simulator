# Memory Allocation Simulator

A C++-based simulation of contiguous memory allocation techniques used in operating systems. The project demonstrates how different allocation strategies assign memory to processes, manage free memory blocks, and handle deallocation.

## Overview

The Memory Allocation Simulator models a fixed-size memory space divided into allocated and free blocks. Users can create processes, request memory allocation, deallocate processes, view the memory layout, and inspect memory utilization through a menu-driven console interface.

The project implements four memory allocation strategies:

- **First Fit** — Allocates the first free block large enough to accommodate a process.
- **Best Fit** — Allocates the smallest suitable free block.
- **Worst Fit** — Allocates the largest available suitable free block.
- **Next Fit** — Continues searching from the position of the previous allocation.

## Features

- Create processes with unique process IDs and memory requirements.
- Allocate memory using different allocation strategies.
- Deallocate memory associated with a process.
- Split larger free blocks when a process requires only part of the available space.
- Merge adjacent free blocks after deallocation to reduce external fragmentation.
- Display the current memory map, including block addresses, sizes, and allocation status.
- Calculate memory statistics, including:
  - Total memory
  - Used memory
  - Free memory
  - Number of free blocks
  - Largest free block
  - Memory utilization
- Switch between allocation algorithms through a console menu.

## Technologies Used

- **Language:** C++
- **Standard Library:** `iostream`, `vector`
- **Concepts:** Object-Oriented Programming, runtime polymorphism, inheritance, abstraction, and dynamic memory management.

## Project Structure

```text
Memory-Allocation-Simulator/
│
├── main.cpp
├── Simulator.h
├── Simulator.cpp
│
├── Process.h
├── MemoryBlock.h
├── MemoryAllocator.h
│
├── FirstFit.h
├── BestFit.h
├── WorstFit.h
├── NextFit.h
│
└── README.md
```

*Note: Update this structure if your final implementation separates allocator declarations and definitions into additional `.cpp` files.*

## How It Works

### 1. Process Management

Each process contains:
- A unique Process ID (PID).
- A requested memory size.

Creating a process does not automatically allocate memory. Allocation is a separate operation.

### 2. Memory Representation

Memory is represented as a collection of `MemoryBlock` objects rather than individual memory units.

Each block stores:
- Starting address
- Block size
- Process ID occupying the block

A process ID of `-1` indicates that the block is free.

### 3. Allocation

When a process requests memory, the selected allocation algorithm searches the memory blocks for a suitable free block.

If a block is larger than the requested size, it is split into:
- An allocated block for the process.
- A remaining free block.

If no suitable block is available, the allocation fails.

### 4. Deallocation

When a process is deallocated, its memory block is marked as free. Adjacent free blocks are then merged into a larger block whenever possible.

This process is known as **coalescing**.

### 5. Runtime Polymorphism

The `MemoryAllocator` base class defines a common interface for the allocation strategies. The derived allocator classes implement their respective algorithms.

The `Simulator` can interact with the selected allocator through a base-class pointer, allowing the allocation strategy to be changed without rewriting the simulator's main logic.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later.
- Git (optional, for cloning the repository).
- A code editor such as Visual Studio Code.

### Installation

Clone the repository:

```bash
git clone <repository-url>
cd Memory-Allocation-Simulator
```

Replace `<repository-url>` with your GitHub repository URL.

### Compilation

If your project is implemented entirely in header files alongside `main.cpp` and `Simulator.cpp`, compile with:

```bash
g++ -std=c++11 main.cpp Simulator.cpp -o simulator
```

If your allocator implementations are in separate `.cpp` files, include those files in the compilation command as well.

### Run the Simulator

On Windows:

```bash
simulator.exe
```

On Linux or macOS:

```bash
./simulator
```

## Usage

After starting the program, use the menu to perform operations such as:

1. Create a process.
2. Allocate memory to a process.
3. Deallocate a process.
4. Display the memory map.
5. View memory statistics.
6. Change the allocation algorithm.
7. Exit.

The available menu options depend on the final implementation.

## Example

Suppose the simulator manages 1000 KB of memory.

Initially:

```text
Start    Size    Status
0        1000    FREE
```

After allocating 300 KB to process P1:

```text
Start    Size    Status
0        300     P1
300      700     FREE
```

After allocating another 200 KB to process P2:

```text
Start    Size    Status
0        300     P1
300      200     P2
500      500     FREE
```

After deallocating P1 and merging adjacent free blocks where possible:

```text
Start    Size    Status
0        300     FREE
300      200     P2
500      500     FREE
```

The two free blocks in this example are separated by P2, so they cannot be merged.

## Learning Objectives

This project provides practical experience with:

- Implementing memory allocation strategies.
- Understanding contiguous memory management.
- Applying inheritance and abstraction in C++.
- Using runtime polymorphism through virtual functions.
- Managing collections with `std::vector`.
- Implementing block splitting and coalescing.
- Calculating memory utilization and understanding external fragmentation.
- Collaborating through Git and GitHub branches.

## Limitations

- The project simulates memory allocation; it does not allocate actual system RAM.
- Memory is represented using a fixed-size address space.
- Processes are modeled using a PID and requested memory size.
- Allocation success depends on the availability of a sufficiently large contiguous free block.

## Future Improvements

Potential enhancements include:

- A graphical memory-map visualization.
- Comparison of all four allocation strategies using identical workloads.
- More detailed external-fragmentation statistics.
- Input validation and improved error handling.
- Automated test cases for allocation, deallocation, splitting, and coalescing.
- Exporting simulation results to a file.

## Contributors

- [Shloke Ghoshal]
- [Prasit Raithatha]

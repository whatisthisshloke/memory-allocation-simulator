#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class Simulator
{
private:
    int totalMemory;

    MemoryAllocator* allocator;

    std::vector<Process> processes;
    std::vector<MemoryBlock> memory;

    void showMenu();

    void createProcess();
    void allocateProcess(int* nextptr);
    void deallocateProcess(int* nextptr);

    void displayMemory();
    void showStatistics();

    void changeAlgorithm(
        int* nextptr
    );

public:
    Simulator(int Memory);
    ~Simulator();

    Simulator(const Simulator&) = delete;
    Simulator& operator=(const Simulator&) = delete;

    void run(
        int* nextptr
    );
};

#endif
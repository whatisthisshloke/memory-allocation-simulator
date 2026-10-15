#ifndef SIMULATOR_H
#define SIMULATOR_H

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

    Process* createProcess();
    void allocateProcess(int* nextptr);
    void deallocateProcess(int* nextptr);

    void displayMemory();
    void showStatistics();

    void changeAlgorithm(
        std::vector<MemoryBlock>& memory,
        Process p,
        int* nextptr
    );

public:
    Simulator(int memory);

    void run(
        std::vector<MemoryBlock>& memory,
        Process p,
        int* nextptr
    );

    ~Simulator();
};

#endif
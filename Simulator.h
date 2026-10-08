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

    void showMenu();

    void createProcess();
    void allocateProcess();
    void deallocateProcess();

    void displayMemory();
    void showStatistics();

    void changeAlgorithm();

public:
    Simulator(int memory);

    void run();

    ~Simulator();
};

#endif
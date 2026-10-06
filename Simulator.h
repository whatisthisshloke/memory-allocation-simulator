#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "MemoryAllocator.h"

class Simulator
{
private:
    MemoryAllocator* allocator;

public:
    Simulator(int totalMemory);

    void run();
};

#endif
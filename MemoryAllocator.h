#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include "Process.h"

class MemoryAllocator
{
public:
    virtual bool allocate(Process p) = 0;

    virtual bool deallocate(int pid) = 0;

    virtual void display() = 0;

    virtual ~MemoryAllocator() {}
};

#endif
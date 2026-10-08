#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include "Process.h"
#include "MemoryBlock.h"
#include <vector>

class MemoryAllocator
{
public:
    virtual ~MemoryAllocator() = default;
    
    virtual bool allocate(
        Process p, 
        std::vector<MemoryBlock>& memory
    ) = 0;
    virtual bool deallocate(
        Process p, 
        std::vector<MemoryBlock>& memory
    ) = 0;

    virtual int getTotalMemory() const = 0;
    virtual int getUsedMemory() const = 0;
    virtual int getFreeMemory() const = 0;
    virtual int getFreeBlockCount() const = 0;
    virtual int getLargestFreeBlock() const = 0;

    virtual const std::vector<MemoryBlock>& getMemoryBlocks() const = 0;


};

#endif
#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include "Process.h"
#include "MemoryBlock.h"
#include <vector>
#include <algorithm>

class MemoryAllocator
{
public:
    virtual ~MemoryAllocator() = default;
    virtual bool allocate(
        Process p, 
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    ) = 0;

    bool deallocate(
        Process p, 
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    )
    {
        bool found = false;

        for (int i = 0; i < (int)memory.size(); i++)
        {
            if (memory[i].getProcessId() == p.getPid())
            {
                memory[i] = MemoryBlock(
                    memory[i].getStart(),
                    memory[i].getSize(),
                    -1
                );
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }

        for (int i = 0; i < (int)memory.size() - 1; )
        {
            if (memory[i].getProcessId() == -1 &&
                memory[i + 1].getProcessId() == -1)
            {
                int combinedSize =
                    memory[i].getSize() +
                    memory[i + 1].getSize();

                memory[i] = MemoryBlock(
                    memory[i].getStart(),
                    combinedSize,
                    -1
                );

                memory.erase(memory.begin() + i + 1);
            }
            else
            {
                i++;
            }
        }

        if (nextIndex && *nextIndex >= (int)memory.size())
        {
            *nextIndex = 0;
        }

        return true;
    }

    int getTotalMemory(const std::vector<MemoryBlock>& memory) const
    {
        int total = 0;
        for (size_t i = 0; i < memory.size(); i++)
        {
            total += memory[i].getSize();
        }
        return total;
    }

    int getUsedMemory(const std::vector<MemoryBlock>& memory) const
    {
        int used = 0;
        for (size_t i = 0; i < memory.size(); i++)
        {
            if (!memory[i].isFree())
            {
                used += memory[i].getSize();
            }
        }
        return used;
    }

    int getFreeMemory(const std::vector<MemoryBlock>& memory) const
    {
        int free = 0;
        for (size_t i = 0; i < memory.size(); i++)
        {
            if (memory[i].isFree())
            {
                free += memory[i].getSize();
            }
        }
        return free;
    }

    int getFreeBlockCount(const std::vector<MemoryBlock>& memory) const
    {
        int freeCount = 0;
        for (size_t i = 0; i < memory.size(); i++)
        {
            if (memory[i].isFree())
            {
                freeCount++;
            }
        }
        return freeCount;
    }

    int getLargestFreeBlock(const std::vector<MemoryBlock>& memory) const
    {
        int lSize = 0;
        for (size_t i = 0; i < memory.size(); i++)
        {
            if (memory[i].isFree())
            {
                lSize = std::max(memory[i].getSize(), lSize);
            }
        }
        return lSize;
    }
};

#endif
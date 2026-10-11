#ifndef NEXRFIT_H
#define NEXTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class firstFit : public MemoryAllocator {
public:
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    ) override
    {
        for (int i = *nextIndex; i < (int)memory.size(); i++)
        {
            if (memory[i].getProcessId() == -1 &&
                memory[i].getSize() >= p.getSize())
            {
                int start = memory[i].getStart();
                int originalSize = memory[i].getSize();
                int processSize = p.getSize();

                MemoryBlock allocated(
                    start, processSize, p.getPid()
                );
                memory[i] = allocated;

                if (originalSize > processSize)
                {
                    MemoryBlock freeBlock(
                        start + processSize,
                        originalSize - processSize,
                        -1
                    );
                    memory.insert(memory.begin() + i + 1, freeBlock);
                }
                *nextIndex = i;
                return true;
            }
        }
        return false;
    }
};

#endif
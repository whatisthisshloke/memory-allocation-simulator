#ifndef NEXTFIT_H
#define NEXTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class nextFit : public MemoryAllocator {
public:
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    ) override
    {
        if (memory.empty()) return false;
        int n = (int)memory.size();
        int startIndex = 0;
        if (nextIndex && *nextIndex >= 0 && *nextIndex < n)
        {
            startIndex = *nextIndex;
        }

        for (int step = 0; step < n; step++)
        {
            int i = (startIndex + step) % n;
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
                if (nextIndex)
                {
                    *nextIndex = i;
                }
                return true;
            }
        }
        return false;
    }
};

#endif
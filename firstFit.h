#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class firstFit : public MemoryAllocator
{
public:
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override
    {
        for (int i = 0; i < (int)memory.size(); i++)
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
                return true;
            }
        }
        return false;
    }

    bool deallocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override
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
        return true;
    }
};

#endif
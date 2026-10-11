#ifndef WORSTFIT_H
#define WORSTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>
#include <algorithm>

class firstFit : public MemoryAllocator {
public:
    public:
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override
    {
        int worstIndex = -1;
        for (int i = 0; i < (int)memory.size(); i++)
        {
            if(memory[i].getProcessId() == -1 && memory[i].getSize()>=p.getSize()){
                if (worstIndex == 0 || memory[i].getSize() > memory[worstIndex].getSize()){
                    worstIndex = i;
                }
            }
        }
        if(worstIndex!=-1){
            int start = memory[worstIndex].getStart();
            int originalSize = memory[worstIndex].getSize();
            int processSize = p.getSize();

            MemoryBlock allocated(
            start, processSize, p.getPid()
            );
            memory[worstIndex] = allocated;

            if (originalSize > processSize)
            {
                MemoryBlock freeBlock(
                start + processSize,
                originalSize - processSize,
                -1
                );
                memory.insert(memory.begin() + worstIndex + 1, freeBlock);
            }
            return true;
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
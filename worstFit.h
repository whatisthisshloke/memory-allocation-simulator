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
        std::vector<MemoryBlock>& memory,
        int *nextIndex
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
            *nextIndex = worstIndex;
            return true;
        }
        return false;
    }

};

#endif
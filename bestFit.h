#ifndef BESTFIT_H
#define BESTFIT_H

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
        int BestIndex = -1;
        for (int i = 0; i < (int)memory.size(); i++)
        {
            if(memory[i].getProcessId() == -1 && memory[i].getSize()>=p.getSize()){
                if (BestIndex == 0 || memory[i].getSize() < memory[BestIndex].getSize()){
                    BestIndex = i;
                }
            }
        }
        if(BestIndex!=-1){
            int start = memory[BestIndex].getStart();
            int originalSize = memory[BestIndex].getSize();
            int processSize = p.getSize();

            MemoryBlock allocated(
            start, processSize, p.getPid()
            );
            memory[BestIndex] = allocated;

            if (originalSize > processSize)
            {
                MemoryBlock freeBlock(
                start + processSize,
                originalSize - processSize,
                -1
                );
                memory.insert(memory.begin() + BestIndex + 1, freeBlock);
            }
            *nextIndex = BestIndex;
            return true;
        }
        return false;
    }
};

#endif
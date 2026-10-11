#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class firstFit : public MemoryAllocator {
public:
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override{
        for (int i = 0; i < memory.size(); i++){
            if(memory[i].getSize() >= p.getSize() ){
                int start = memory[i-1].getSize()+1;
                int size = p.getSize();
                MemoryBlock allocated(start,p.getSize(),p.getPid());
                MemoryBlock freeBlock(start,memory[i].getSize() - size);
                memory[i] = allocated;
                memory[i+1] = freeBlock;
            }
        }
    }

    bool deallocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override;
};

#endif
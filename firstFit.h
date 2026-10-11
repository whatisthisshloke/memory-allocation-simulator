#ifndef FIRSTFIT_H
#define FIRSTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class firstFit : public MemoryAllocator
{
public:
<<<<<<< HEAD
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    ) override
=======
    bool allocate(Process p, std::vector<MemoryBlock>& memory) override
>>>>>>> 806ed820c14a26fdc743d7ceb3ad7232ce0f32c1
    {
        for (int i = 0; i < (int)memory.size(); i++){
            if (memory[i].getProcessId() == -1 && memory[i].getSize() >= p.getSize()){
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
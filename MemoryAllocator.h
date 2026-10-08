#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include "process.h"
#include "memoryBlock.h"
#include "first_fit.h"
#include "next_fit.h"
#include "best_fit.h"

class MemoryAllocator
{
public:
    virtual bool allocate(process p, vector<MemoryBlock> memory){
        for(int i = 0; i< sizeof(memory); i++){
            if (memory[i].isFree()){
                
            }
        }
    };

    virtual bool deallocate(int pid) = 0;

    virtual void display() = 0;

    virtual ~MemoryAllocator() {}
};

#endif
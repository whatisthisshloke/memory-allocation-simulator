#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include "MemoryAllocator.h"
#include "process.h"

class MemoryBlock
{
private:
    int start;
    int size;
    int processId;

public:
    MemoryBlock(int s, int sz, int pid=-1)
    {
        start = s;
        size = sz;
        processId = pid;
    }

    int getStart()
    {
        return start;
    }

    int getSize()
    {
        return size;
    }

    int getProcessId()
    {
        return processId;
    }
    bool isFree (){
        if (processId == -1){
            return true;
        }
        else {
            false;
        }
    }
    void allocate(int pid, int reqSize){
        processId = pid;
        size = reqSize;
        return;
    }
    void free(){
        size = 0;
        processId = -1;
    }
};

#endif
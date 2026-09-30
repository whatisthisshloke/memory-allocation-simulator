#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

class MemoryBlock
{
private:
    int start;
    int size;
    int processId;

public:
    MemoryBlock(int s, int sz, int pid)
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
};

#endif
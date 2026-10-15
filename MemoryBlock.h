#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

class MemoryBlock
{
private:
    int start;
    int size;
    int processId;

public:
    MemoryBlock(int s = 0, int sz = 0, int pid = -1)
    {
        start = s;
        size = sz;
        processId = pid;
    }

    int getStart() const
    {
        return start;
    }

    int getSize() const
    {
        return size;
    }

    int getProcessId() const
    {
        return processId;
    }

    bool isFree() const
    {
        return processId == -1;
    }

    void allocate(int pid, int reqSize)
    {
        processId = pid;
        size = reqSize;
    }

    void free()
    {
        processId = -1;
    }
};

#endif
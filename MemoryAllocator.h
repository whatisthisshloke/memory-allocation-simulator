#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include "Process.h"
#include "MemoryBlock.h"
#include <vector>
#include <algorithm>

class MemoryAllocator
{
public:
    virtual ~MemoryAllocator() = default;
    
    virtual bool allocate(
        Process p, 
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    ) = 0;

    bool deallocate(
        Process p, 
        std::vector<MemoryBlock>& memory,
        int *nextIndex
    )
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

        for (int i = 0; i < (int)memory.size() - 1; i++ )
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
                *nextIndex = i;

                memory.erase(memory.begin() + i + 1);
            }
            else
            {
                i++;
            }
        }
        return true;
    }
    

    int getTotalMemory(vector<MemoryBlock>& memory){
        return 1000;
    }
    int getUsedMemory(vector<MemoryBlock>& memory){
        int used = 0;
        for(int i = 0; i < (int)memory.size(); i++ ){
            if(!memory[i].isFree()){
                used += memory[i].getSize();
            }
            return used;
        }
    }
    int getFreeMemory(vector<MemoryBlock>& memory){
        int free = 0;
        for(int i = 0; i < (int)memory.size(); i++ ){
            if(memory[i].isFree()){
                free += memory[i].getSize();
            }
            return free;
        }
    }
    int getFreeBlockCount(vector<MemoryBlock>& memory){
        int freeCount = 0;
        for(int i = 0; i < (int)memory.size(); i++ ){
            if(memory[i].isFree()){
                freeCount ++;
            }
            return freeCount;
        }
    }
    int getLargestFreeBlock(vector<MemoryBlock>& memory){
        int lSize = 0;
        for(int i = 0; i < (int)memory.size(); i++ ){
            if(!memory[i].isFree()){
                lSize = max(memory[i].getSize(), lSize);
            }
            return lSize;
        }
    }

    virtual const std::vector<MemoryBlock>& getMemoryBlocks(vector<MemoryBlock>& memory) const = 0;

};

#endif
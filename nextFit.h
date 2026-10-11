#ifndef NEXRFIT_H
#define NEXTFIT_H

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include <vector>

class firstFit : public MemoryAllocator {
public:
    bool allocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override;

    bool deallocate(
        Process p,
        std::vector<MemoryBlock>& memory
    ) override;
};

#endif
#include <iostream>
#include <vector>

#include "Process.h"
#include "MemoryBlock.h"
#include "MemoryAllocator.h"
#include "Simulator.h"
#include "SimulatorRunner.h"

using namespace std;

int main()
{
    cout << "***Memory Allocation Simulator***" << endl;
    vector<MemoryBlock> memory;
    memory.push_back(MemoryBlock(0,1000));
    int nextIndex = 0;
    return 0;
}

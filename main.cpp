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
    int totalmem;
    cout << "***Memory Allocation Simulator***" << endl;
    cout << " Enter the total Memory: ";
    if (!(cin >> totalmem) || totalmem <= 0)
    {
        cout << "Invalid total memory! Exiting.\n";
        return 1;
    }
    int nextIndex = 0;
    Simulator sim(totalmem);
    sim.run(&nextIndex);
    return 0;
}

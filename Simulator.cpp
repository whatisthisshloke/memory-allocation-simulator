#include "Simulator.h"
#include <iostream>

using namespace std;

Simulator::Simulator(int totalMemory)
{
    allocator = nullptr;
}

void Simulator::run()
{
    cout << "==============================\n";
    cout << " Memory Allocation Simulator\n";
    cout << "==============================\n";

    cout << "Simulator started.\n";
}
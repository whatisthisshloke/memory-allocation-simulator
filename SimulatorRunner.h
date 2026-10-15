#ifndef SIMULATORRUNNER_H
#define SIMULATORRUNNER_H

#include <iostream>
#include "Simulator.h"
#include "firstFit.h"
#include "worstFit.h"
#include "bestFit.h"
#include "nextFit.h"

using namespace std;

Simulator::Simulator(int memorySize)
{
    totalMemory = memorySize;
    allocator = nullptr;
    MemoryBlock block(0, memorySize, -1);
    memory.push_back(block);
}

Simulator::~Simulator()
{
    delete allocator;
    allocator = nullptr;
}

void Simulator::showMenu()
{
    cout << "\n====================================\n";
    cout << "      MEMORY ALLOCATION SIMULATOR\n";
    cout << "====================================\n";

    cout << "1. Create Process\n";
    cout << "2. Allocate Memory\n";
    cout << "3. Deallocate Process\n";
    cout << "4. Display Memory Map\n";
    cout << "5. Memory Statistics\n";
    cout << "6. Change Algorithm\n";
    cout << "7. Exit\n";

    cout << "====================================\n";
}

void Simulator::run(
    int* nextptr
)
{
    int choice;
    
    do {
        showMenu();

        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input!!\n";
            continue;
        }

        switch (choice) {
            case 1:
                createProcess();
                break;
            case 2:
                allocateProcess(nextptr);
                break;
            case 3:
                deallocateProcess(nextptr);
                break;
            case 4:
                displayMemory();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                changeAlgorithm(nextptr);
                break;
            case 7:
                cout << "Exiting simulator!!\n";
                break;  
            default:
                cout << "Invalid Choice!!\n";
        }
    } while (choice != 7);
}

void Simulator::createProcess()
{
    int pid;
    int size;

    cout << "\nEnter Process ID: ";
    if (!(cin >> pid)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!!\n";
        return;
    }

    cout << "Enter Process Size (in KB): ";
    if (!(cin >> size)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!!\n";
        return;
    }

    if (pid <= 0 || size <= 0) {
        cout << "Invalid input!!\n";
        return;
    }

    for (const Process& p : processes) {
        if (p.getPid() == pid) {
            cout << "Process already exists!!\n";
            return;
        }
    }

    Process p(pid, size);
    processes.push_back(p);

    cout << "Process created successfully!!\n";
}

void Simulator::allocateProcess(int* nextptr)
{
    if (allocator == nullptr) {
        cout << "Please select an algorithm first!!\n";
        return;
    }

    int pid;
    cout << "\nEnter Process ID to allocate memory: ";
    if (!(cin >> pid)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!!\n";
        return;
    }

    for (const MemoryBlock& blk : memory) {
        if (blk.getProcessId() == pid) {
            cout << "Process " << pid << " is already allocated!!\n";
            return;
        }
    }

    for (Process& p : processes) {
        if (p.getPid() == pid) {
            if (allocator->allocate(p, memory, nextptr)) {
                cout << "Memory allocated successfully for Process " << pid << "\n";
            } else {
                cout << "Memory allocation failed for Process " << pid << "\n";
            }
            return;
        }
    }

    cout << "Process not found!!\n";
}

void Simulator::deallocateProcess(int* nextptr)
{
    if (allocator == nullptr) {
        cout << "Please select an algorithm first!!\n";
        return;
    }

    int pid;
    cout << "\nEnter Process ID to deallocate memory: ";
    if (!(cin >> pid)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!!\n";
        return;
    }

    for (Process& p : processes) {
        if (p.getPid() == pid) {
            if (allocator->deallocate(p, memory, nextptr)) {
                cout << "Process deallocated successfully!!\n";
            } else {
                cout << "Process is not currently allocated!!\n";
            }
            return;
        }
    }

    cout << "Process not found!!\n";
}

void Simulator::displayMemory()
{
    cout << "\n========== MEMORY MAP ==========\n"; 
    cout << "Start\tSize\tStatus\n"; 
    cout << "-------------------------------\n";

    for (const MemoryBlock& blk : memory) {
        cout << blk.getStart() << "\t";
        cout << blk.getSize() << "\t";
        
        if (blk.getProcessId() == -1) {
            cout << "FREE";
        } else {
            cout << "P" << blk.getProcessId();
        }

        cout << endl;
    }
    cout << "================================\n";
}

void Simulator::showStatistics()
{
    int used = 0;
    int freeMemory = 0;
    int freeBlocks = 0;
    int largestFreeBlock = 0;

    for (const MemoryBlock& blk : memory) {
        if (blk.getProcessId() == -1) {
            freeMemory += blk.getSize();
            freeBlocks++;
            if (blk.getSize() > largestFreeBlock) {
                largestFreeBlock = blk.getSize();
            }
        } else {
            used += blk.getSize();
        }
    }   

    cout << "\n======= MEMORY STATISTICS =======\n"; 
    cout << "Total Memory : " << totalMemory << " KB\n"; 
    cout << "Used Memory : " << used << " KB\n"; 
    cout << "Free Memory : " << freeMemory << " KB\n"; 
    cout << "Free Blocks : " << freeBlocks << "\n"; 
    cout << "Largest Free Block : " << largestFreeBlock << " KB\n"; 
    if (totalMemory > 0) { 
        double utilization = (double)used / totalMemory * 100.0; 
        cout << "Memory Utilization : " << utilization << "%\n";  
    }
    cout << "=================================\n"; 
}

void Simulator::changeAlgorithm(
    int* nextptr
)
{
    int choice;
    cout << "\n===== SELECT ALLOCATION ALGORITHM =====\n";
    cout << "1. First Fit\n";
    cout << "2. Best Fit\n";
    cout << "3. Worst Fit\n";
    cout << "4. Next Fit\n";
    cout << "Enter your choice: ";

    if (!(cin >> choice) || choice < 1 || choice > 4)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid algorithm choice.\n";
        return;
    }

    delete allocator;
    allocator = nullptr;

    switch (choice)
    {
        case 1:
            allocator = new firstFit();
            cout << "First Fit selected.\n";
            break;
        case 2:
            allocator = new bestFit();
            cout << "Best Fit selected.\n";
            break;
        case 3:
            allocator = new worstFit();
            cout << "Worst Fit selected.\n";
            break;
        case 4:
            allocator = new nextFit();
            if (nextptr) {
                *nextptr = 0;
            }
            cout << "Next Fit selected.\n";
            break;
    }
}

#endif

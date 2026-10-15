#include <iostream>
#include "Simulator.h"
#include "firstFit.h"
#include "worstFit.h"
#include "bestFit.h"
#include "nextFit.h"


using namespace std;

Simulator::Simulator(int memory)
{
    totalMemory = memory;
    allocator = nullptr;
}

Simulator::~Simulator()
{
    delete allocator;
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
    vector<MemoryBlock>& memory,
    int* nextptr
)
{
    Process* p;
    int choice;
    
    do {
        showMenu();

        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice){
            case 1:
                p = createProcess();
                break;
            case 2:
                allocateProcess(*p, nextptr);
                break;
            case 3:
                deallocateProcess(*p, nextptr);
                break;
            case 4:
                displayMemory(memory);
                break;
            case 5:
                showStatistics(memory);
                break;
            case 6:
                p = createProcess();
                changeAlgorithm(memory, *p, nextptr);
                break;
            case 7:
                cout<<"Exiting simulator!!\n";
                break;  
            default:
                cout<<"Invalid Choice!!\n";
                
        }
    } while(choice!=7);

}

Process* Simulator::createProcess()
{
    int pid;
    int size;

    cout<<"\nEnter Process ID:";
    cin>>pid;

    cout<<"\n Enter Process Size(in KB):";
    cin>>size;

    if(pid<=0 || size<=0){
        cout<<"Invalid input!!\n";
        return;
    }

    for(Process& p : processes){
        if(p.getPid()==pid);
        cout<<"Process already exists!!\n";
        return;
    }

    Process p(pid, size);
    processes.push_back(p);  //push_back helps append at the end of a vector

    cout<<"Process created successfully!!\n";
    return &p;
}

void Simulator::allocateProcess(int* nextptr)
{
    if(allocator==nullptr){
        cout<<"Please select an algorithm first!!\n";
        return;
    }

    int pid;
    cout<<"\nEnter Process ID to allocate memory:";
    cin>>pid;

    for(Process& p : processes){
        if(p.getPid() == pid){
            if(allocator->allocate(p, memory, nextptr)){
                cout<<"Memory allocated successfully for Process "<<pid<<"\n";
            } else {
                cout<<"Memory allocation failed for Process "<<pid<<"\n";
            }

            return;
        }
    }

    cout<<"Process not found!!\n";
}

void Simulator::deallocateProcess(int* nextptr)
{
    if(allocator==nullptr){
        cout<<"Please select an algorithm first!!\n";
        return;
    }

    int pid;
    cout<<"Enter Process ID to deallocate memory:";
    cin>>pid;

    for(Process& p : processes){
        if(p.getPid()== pid){
            if(allocator->deallocate(p, memory, nextptr)){
                cout<<"Process deallocated successfully!!\n";
            }else{
                cout<<"Process is not currently allocated!!\n";
            }

            return;
        }
        
        cout<<"Process not found";
    }
}

void Simulator::displayMemory(){
    if(allocator==nullptr){
        cout<<"Please select an algorithm first!!\n";
        return;
    }

    cout << "\n========== MEMORY MAP ==========\n"; 
    cout << "Start\tSize\tStatus\n"; 
    cout << "-------------------------------\n";

    for(MemoryBlock& blk : memory){
        cout<<blk.getStart()<<"\t";
        cout<<blk.getSize()<<"\t";
        
        if(blk.getProcessId()==-1){
            cout<<"Free";
            cout<<"Free";
        }else{
            cout<<"P"<<blk.getProcessId();
        }

        cout<<endl;
    }
    cout << "================================\n";
}

void Simulator::showStatistics(){
    
    int totalMemory;
    int used=0;
    int freeMemory=0;
    int freeBlocks=0;
    int largestFreeBlock=0;

    for(MemoryBlock& blk : memory){
        if(blk.getProcessId()==-1){
            freeMemory += blk.getSize();
            freeBlocks++;
        }

        if(blk.getSize()>largestFreeBlock){
            largestFreeBlock=blk.getSize();
        }else{
            used+=blk.getSize();
        }
    }   

    cout << "\n======= MEMORY STATISTICS =======\n"; 
    cout << "Total Memory : " << totalMemory << " KB\n"; 
    cout << "Used Memory : " << used << " KB\n"; 
    cout << "Free Memory : " << freeMemory << " KB\n"; 
    cout << "Free Blocks : " << freeBlocks << "\n"; 
    cout << "Largest Free Block : " << largestFreeBlock << " KB\n"; 
    if (totalMemory > 0) { 
    double utilization = (double)used / totalMemory * 100; 
    cout << "Memory Utilization : " << utilization << "%\n";  
    cout << "=================================\n"; 
    }
}

void Simulator::changeAlgorithm(
    Process p,
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

    cin >> choice;

    if (choice < 1 || choice > 4)
    {
        cout << "Invalid algorithm choice.\n";
        return;
    }

    delete allocator;
    allocator = nullptr;

    switch (choice)
    {
        case 1:
            firstFit* newFirst;
            newFirst->allocate(p, memory, nextptr);
            cout << "First Fit selected.\n";
            break;

        case 2:
            bestFit* newBest;
            newBest->allocate(p, memory, nextptr);
            cout << "Best Fit selected.\n";
            break;

        case 3:
            worstFit* newWorst;
            newWorst->allocate(p, memory, nextptr);
            cout << "Worst Fit selected.\n";
            break;

        case 4:
            nextFit* newNext;
            newNext->allocate(p, memory, nextptr);
            cout << "Next Fit selected.\n";
            break;
    }
}





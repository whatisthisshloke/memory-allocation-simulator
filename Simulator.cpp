#include "Simulator.h"
#include "firstFit.h"
#include "worstFit.h"
#include "bestFit.h"
#include "nextFit.h"
#include <iostream>

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

void Simulator::run()
{
    int choice;
    
    do {
        showMenu();

        cout<<"Enter your choice:";
        cin>>choice;

        switch(choice){
            case 1:
                createProcess();
                break;
            case 2:
                allocateProcess();
                break;
            case 3:
                deallocateProcess();
                break;
            case 4:
                displayMemory();
                break;
            case 5:
                showStatistics();
                break;
            case 6:
                changeAlgorithm();
                break;
            case 7:
                cout<<"Exiting simulator!!\n";
                break;  
            default:
                cout<<"Invalid Choice!!\n";
                
        }
    } while(choice!=7);

}

void Simulator::createProcess()
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
}

void Simulator::allocateProcess()
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
            if(allocator->allocate(p, memory)){
                cout<<"Memory allocated successfully for Process "<<pid<<"\n";
            } else {
                cout<<"Memory allocation failed for Process "<<pid<<"\n";
            }

            return;
        }
    }

    cout<<"Process not found!!\n";
}

void Simulator::deallocateProcess()
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
            if(allocator->deallocate(p, memory)){
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




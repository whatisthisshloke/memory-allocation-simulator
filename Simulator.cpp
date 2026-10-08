#include "Simulator.h"

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
            if(allocator->allocate(p)){
                cout<<"Memory allocated successfully for Process "<<pid<<"\n";
            } else {
                cout<<"Memory allocation failed for Process "<<pid<<"\n";
            }

            return;
        }
    }

    cout<<"Process not found!!\n";
}


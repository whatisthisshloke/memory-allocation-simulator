#ifndef PROCESS_H
#define PROCESS_H

class Process
{
private:
    int pid;
    int size;

public:
    Process(int id = 0, int s = 0) // Process Constructor
    {
        pid = id;
        size = s;
    }

    int getPid() const // Retrieving Process ID
    {
        return pid;
    }

    int getSize() const // Retrieving Process Size
    {
        return size;
    }
};

#endif
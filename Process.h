#ifndef PROCESS_H
#define PROCESS_H

class Process
{
private:
    int pid;
    int size;

public:
    Process(int id, int s) //Process Constructor
    {
        pid = id;
        size = s;
    }

    int getPid() //Retreiving Process ID
    {
        return pid;
    }

    int getSize() //Retreiving Process Size
    {
        return size;
    }
};

#endif
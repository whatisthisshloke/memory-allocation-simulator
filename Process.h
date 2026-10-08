#ifndef PROCESS_H
#define PROCESS_H

class Process
{
private:
    int pid;
    int size;

public:
    Process(int id, int s)
    {
        pid = id;
        size = s;
    }

    int getPid()
    {
        return pid;
    }

    int getSize()
    {
        return size;
    }
};

#endif
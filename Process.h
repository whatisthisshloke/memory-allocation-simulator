#ifndef PROCESS_H
#define PROCESS_H

class process
{
private:
    int pid;
    int size;

public:
    process(int id, int s)
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
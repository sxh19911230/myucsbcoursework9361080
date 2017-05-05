// pcb.h
//  The process control block is a data structure used to keep track of a
//	single user process. For now, each process has an ID, a parent and a
//	pointer to its kernel thread.

#ifndef PCB_H
#define PCB_H
#include "system.h"
#include "list.h"

class PCB {

public:
    PCB(int pid, int parentPid);
    ~PCB();

    int pid;            // Process ID
    int parentPid;      // Parent's Process ID
    Thread *thread;     // Kernel thread that controls this process
    List *queue;
    int fd[16];
    int byteRead[16];
};

#endif // PCB_H

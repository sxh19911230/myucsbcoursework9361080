// pcb.cc
//

#include "pcb.h"

//----------------------------------------------------------------------
// PCB::PCB
//  Allocate a new process control block and initialize it with process
//  ID and a parent.
//----------------------------------------------------------------------

PCB::PCB(int pid, int parentPid)
{
    this->pid = pid;
    this->parentPid = parentPid;
    queue = NULL;
    fd[0] = fd[1] = fd[2] = 9;
    for(int i = 3; i < 16; i++) {
      fd[i] = -1;
      byteRead[i] = 0;
    }
   
}

//----------------------------------------------------------------------
// PCB::~PCB
//  Deallocate a process control block.
//----------------------------------------------------------------------

PCB::~PCB()
{
    if (queue) delete queue;
}

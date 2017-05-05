// processmanager.cc
//

#include "processmanager.h"

//----------------------------------------------------------------------
// ProcessManager::ProcessManager
//  Create a new process manager to manager MAX_PROCESSES processes.
//----------------------------------------------------------------------

ProcessManager::ProcessManager()
{
    pids = new BitMap(MAX_PROCESSES);
    //pids->Mark(0);
    pidPcb = new std::map<int,PCB*>();
    
}

//----------------------------------------------------------------------
// ProcessManager::~ProcessManager
//  Deallocate a process manager.
//----------------------------------------------------------------------

ProcessManager::~ProcessManager()
{
    delete pids;
    delete pidPcb;
}

//----------------------------------------------------------------------
// ProcessManager::allocPid
//  Allocate an unused PID to be used by a process.
//
//  For now do nothing.
//----------------------------------------------------------------------

int ProcessManager::allocPid()
{
    int i = pids->Find();
    return i;
}

//----------------------------------------------------------------------
// ProcessManager::freePid
//  Deallocate a PID that is in use so that it can be allocated again by
//  another process.
//
//  For now do nothing.
//----------------------------------------------------------------------

void ProcessManager::freePid(int pid)
{
    pids->Clear(pid);
}

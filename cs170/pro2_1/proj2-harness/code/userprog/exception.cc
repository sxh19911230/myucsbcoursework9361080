// exception.cc
//  Entry point into the Nachos kernel from user programs.
//  There are two kinds of things that can cause control to
//  transfer back to here from user code:
//
//  syscall -- The user code explicitly requests to call a procedure
//  in the Nachos kernel.  Right now, the only function we support is
//  "Halt".
//
//  exceptions -- The user code does something that the CPU can't handle.
//  For instance, accessing memory that doesn't exist, arithmetic errors,
//  etc.
//
//  Interrupts (which can also cause control to transfer from user
//  code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include <stdio.h>
#include <string.h>
#include "copyright.h"
#include "syscall.h"
#include "system.h"
#include "machine.h"
#include "pcb.h"
#include "../threads/system.h"
#include "../machine/machine.h"
#include "addrspace.h"
#include "../filesys/openfile.h"
#include <stdexcept>

#define MAX_FILENAME 256

#define USER_READ 0
#define USER_WRITE 1

void doExit();
int doExec();
void doWrite();
void doFork();
void doYield();
void doJoin();
void doCreate();
int doOpen();
void doRead();
void doClose();

int userReadWrite(int virtAddr, char* buffer, int size, int type);

//----------------------------------------------------------------------
// ExceptionHandler
//  Entry point into the Nachos kernel.  Called when a user program
//  is executing, and either does a syscall, or generates an addressing
//  or arithmetic exception.
//
//  For system calls, the following is the calling convention:
//
//  system call code -- r2
//    arg1 -- r4
//    arg2 -- r5
//    arg3 -- r6
//    arg4 -- r7
//
//  The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//  "which" is the kind of exception.  The list of possible exceptions
//  are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int result, type = machine->ReadRegister(2);

    if (which == SyscallException) {
        switch (type) {
            case SC_Halt:
                DEBUG('a', "Shutdown, initiated by user program.\n");
                interrupt->Halt();
                break;
            case SC_Exit:
                DEBUG('a', "Exit() system call invoked.\n");
                doExit();
                break;
            case SC_Exec:
                DEBUG('a', "Exec() system call invoked.\n");
                result = doExec();
                machine->WriteRegister(2, result);
                break;
            case SC_Join:
                DEBUG('a', "Join() system call invoked.\n");
                doJoin();
                break;
            case SC_Create:
                DEBUG('a', "Create() system call invoked.\n");
                doCreate();
                break;
            case SC_Open:
                DEBUG('a', "Open() system call invoked.\n");
                result = doOpen();
                machine->WriteRegister(2, result);
                break;
            case SC_Read:
                DEBUG('a', "Read() system call invoked.\n");
                doRead();
                break;
            case SC_Write:
                DEBUG('a', "Write() system call invoked.\n");
                doWrite();
                break;
            case SC_Close:
                DEBUG('a', "Close() system call invoked.\n");
                doClose();
                break;
            case SC_Fork:
                DEBUG('a', "Fork() system call invoked.\n");
                doFork();
                break;
            case SC_Yield:
                DEBUG('a', "Yield() system call invoked.\n");
                doYield();
                break;
            default:
                printf("Unexpected system call %d. Halting.\n", type);
                interrupt->Halt();
        }
    } else {
        printf("Unexpected user mode exception %d. Halting.\n", which);
        interrupt->Halt();
    }

    // Increment program counter
    machine->WriteRegister(PCReg, machine->ReadRegister(PCReg) + 4);
    machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg) + 4);
    machine->WriteRegister(PrevPCReg, machine->ReadRegister(PrevPCReg) + 4);

}


void joinLauncher(int unused) {
    currentThread->space->RestoreState();
    machine->Run();

}


//----------------------------------------------------------------------
// doExit
//----------------------------------------------------------------------


void doExit()
{
    Thread * t;
    List *queue = currentThread->space->pcb->queue;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    if (queue)
        while (t = (Thread *)queue->Remove()) {
            scheduler->ReadyToRun(t);
        }
    (void) interrupt->SetLevel(oldLevel);
    delete currentThread->space;
    currentThread->Finish();
}

//----------------------------------------------------------------------
// execLauncher
//----------------------------------------------------------------------

void execLauncher(int unused)
{
    AddrSpace *curAddrSpace = currentThread->space;
    curAddrSpace->InitRegisters();
    curAddrSpace->RestoreState();
    machine->Run();
}

//------------------
// forkLauncher
//-----------------
void forkLauncher(int forkAddr)
{
    currentThread->space->RestoreState();
    machine->WriteRegister(PCReg, forkAddr);
    machine->WriteRegister(PrevPCReg, forkAddr-4);
    machine->WriteRegister(NextPCReg, forkAddr+4);
    machine->Run();
}


//----------------------------------------------------------------------
// doExec
//----------------------------------------------------------------------

int doExec()
{
    int filenameVirtAddr = machine->ReadRegister(4);
    int filenamePhysAddr, bytesCopied = 0;
    char *filename = new char [MAX_FILENAME + 1], *kernelPtr = filename;
    char *userPtr, *endOfPage;
    int parentPid;
    OpenFile *execFile;
    AddrSpace *as;

    // First, we need to read the filename of the program to execute out of
    // user memory. This is complicated by the fact that the name might lie
    // across a page boundary.
    do {

        // Find this portion of filename in physical memory
        filenameVirtAddr += bytesCopied;
        filenamePhysAddr = currentThread->space->Translate(filenameVirtAddr);
        userPtr = machine->mainMemory + filenamePhysAddr;

        // Find the end of the page
        endOfPage = machine->mainMemory + (filenamePhysAddr / PageSize + 1)
                                           * PageSize;

        // Copy characters until the string or page ends
        while (*userPtr != '\0' && userPtr != endOfPage) {
            *kernelPtr++ = *userPtr++;
            ++bytesCopied;
        }

    } while (*userPtr != '\0' && bytesCopied != 0);

    *kernelPtr = '\0';

    // Next we need to create a PCB for the new process. The PCB must be
    // initialized with the parent's PID (i.e. that of the current process)
    // and the newly created child's PID.
    DEBUG('b', "parent at: %i\n", currentThread->space->pcb->pid);
    parentPid = processManager->pidPcb->at(currentThread->space->pcb->pid)->parentPid;


    // Finally it needs an address space. We will initialize the address
    // space by loading in the program found in the executable file that was
    // passed in as the first argument.
    execFile = fileSystem->Open(filename);
    as = new AddrSpace(execFile);
    as->pcb->parentPid = parentPid;

    delete execFile;

    // The new process needs a kernel thread by which we can manage its state
    as->pcb->thread = new Thread("child of Exec()");
    as->pcb->thread->space = as;

    // We launch the process with the kernel threads Fork() function. Note
    // that this is different from our implementation of Fork()!
    as->pcb->thread->Fork(execLauncher, 0);
    int pidtmp = as->pcb->pid;
    currentThread->Yield();

    // Because we just overwrote the current thread's address space when we
    // called `new AddrSpace(execFile)` it can no longer be allowed to
    // execute so we call Finish(). You will have to fix this in your
    // implementation once you implement multiple address spaces.

    //delete currentThread->space;
    //currentThread->Finish();

    return pidtmp;
}

//----------------------------------------------------------------------
// doWrite
//----------------------------------------------------------------------

void doWrite()
{
    int userBufVirtAddr = machine->ReadRegister(4);
    int userBufSize = machine->ReadRegister(5);
    int dstFile = machine->ReadRegister(6);

    int i, userBufPhysAddr, bytesToEndOfPage, bytesToCopy, bytesCopied = 0;
    char *kernelBuf = new char[userBufSize + 1];


        // Copy bytes from user memory into kernel memory
        while (bytesCopied < userBufSize) {

            // Perform virtual to physical address translation
            userBufPhysAddr = currentThread->space->Translate(userBufVirtAddr + bytesCopied);


            // Determine how many bytes we can read from this page
            bytesToEndOfPage = PageSize - userBufPhysAddr % PageSize;
            if (userBufSize < bytesToEndOfPage)
                bytesToCopy = userBufSize;
            else
                bytesToCopy = bytesToEndOfPage;

            // Copy bytes into kernel buffer
            memcpy(&kernelBuf[bytesCopied], &machine->mainMemory[userBufPhysAddr], bytesToCopy);
            bytesCopied += bytesToCopy;
        }
     kernelBuf[userBufSize] = '\0';

     if (dstFile == ConsoleOutput) {
        printf("%s", kernelBuf);
        /*
        // Had some bug with console write, so I just use printf :(
        // Write buffer to console (writes should be atomic)

        openFileManager->consoleWriteLock->Acquire();
        for (i = 0; i < userBufSize; ++i)
            UserConsolePutChar(kernelBuf[i]);
        openFileManager->consoleWriteLock->Release();
        */
    } else {
        int sysOpId = currentThread->space->pcb->fd[dstFile];
        OpenFile * o = openFileManager->openFileTable[sysOpId].openFile;
        openFileManager->fileLock[sysOpId]->Acquire();
        o->WriteAt(kernelBuf, userBufSize, 0);
        openFileManager->fileLock[sysOpId]->Release();
    }
    //Also had bug when free this
    //delete[] kernelBuf;
}

void doFork() {
    int forkAddr = machine->ReadRegister(4);
    AddrSpace *as;

    // The new process needs a kernel thread by which we can manage its state

    // Finally it needs an address space. We will initialize the address
    // space by loading in the program found in the executable file that was
    // passed in as the first argument.
    as = new AddrSpace(currentThread->space);
    as->pcb->parentPid=currentThread->space->pcb->pid;
    as->pcb->thread = new Thread("child of Fork()");
    as->pcb->thread->space = as;

    // We launch the process with the kernel threads Fork() function. Note
    // that this is different from our implementation of Fork()!
    as->pcb->thread->Fork(forkLauncher, forkAddr);
    //currentThread->Yield();

}

void doYield() {
    currentThread->space->SaveState();
    currentThread->Yield();
    currentThread->space->RestoreState();
    //machine->Run();
}


void doJoin() {
    PCB *pcb;
    int pidWait = machine->ReadRegister(4);
    DEBUG('b', "joint at: %i\n", currentThread->space->pcb->pid);

    try {
    pcb = processManager->pidPcb->at(pidWait);
    DEBUG('b', "pcb addr: %i\n", pcb);
    if (!pcb->queue)
       pcb->queue = new List;
    pcb->queue->Append((void *)currentThread);

    Thread *nextThread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    //ASSERT(this == currentThread);

    //DEBUG('t', "Yielding thread \"%s\"\n", getName());

    nextThread = scheduler->FindNextToRun();
    if (nextThread != NULL) {
        //scheduler->ReadyToRun(this);
        currentThread->setStatus(BLOCKED);
        scheduler->Run(nextThread);
    }
    (void) interrupt->SetLevel(oldLevel);
    } catch (const std::out_of_range& oor) {};

}

void doCreate() {
    int filenameVirtAddr = machine->ReadRegister(4);
    int filenamePhysAddr, bytesCopied = 0;
    char *filename = new char [MAX_FILENAME + 1], *kernelPtr = filename;
    char *userPtr, *endOfPage;
    do {

        // Find this portion of filename in physical memory
        filenameVirtAddr += bytesCopied;
        filenamePhysAddr = currentThread->space->Translate(filenameVirtAddr);
        userPtr = machine->mainMemory + filenamePhysAddr;

        // Find the end of the page
        endOfPage = machine->mainMemory + (filenamePhysAddr / PageSize + 1)
                                           * PageSize;

        // Copy characters until the string or page ends
        while (*userPtr != '\0' && userPtr != endOfPage) {
            *kernelPtr++ = *userPtr++;
            ++bytesCopied;
        }

    } while (*userPtr != '\0' && bytesCopied != 0);

    *kernelPtr = '\0';
    fileSystem->Create(filename,0);
}

int doOpen() {
    int i, j;
    int fdReturn;
    int filenameVirtAddr = machine->ReadRegister(4);
    int filenamePhysAddr, bytesCopied = 0;
    char *filename = new char [MAX_FILENAME + 1], *kernelPtr = filename;
    char *userPtr, *endOfPage;
    OpenFile *txtFile;
    // First, we need to read the filename of the program to execute out of
    // user memory. This is complicated by the fact that the name might lie
    // across a page boundary.
    do {

        // Find this portion of filename in physical memory
        filenameVirtAddr += bytesCopied;
        filenamePhysAddr = currentThread->space->Translate(filenameVirtAddr);
        userPtr = machine->mainMemory + filenamePhysAddr;

        // Find the end of the page
        endOfPage = machine->mainMemory + (filenamePhysAddr / PageSize + 1)
                                           * PageSize;

        // Copy characters until the string or page ends
        while (*userPtr != '\0' && userPtr != endOfPage) {
            *kernelPtr++ = *userPtr++;
            ++bytesCopied;
        }

    } while (*userPtr != '\0' && bytesCopied != 0);

    *kernelPtr = '\0';

    for (i = 0; i < 16; i++) {
       if (openFileManager->files->Test(i) && !strcmp(openFileManager->openFileTable[i].filename,filename)) {
          openFileManager->openFileTable[i].num++;
          fdReturn = i;
          break;
       }
    }
    
    if (i == 16) {
        txtFile = fileSystem->Open(filename);
        struct SysOpenFile newFile;
        newFile.openFile = txtFile;
        newFile.filename = filename;
        fdReturn = openFileManager->addOpenFile(newFile);
    }
    
    for (i = 0; i < 16; i++) {
        j = currentThread->space->pcb->fd[i];
        if ( j == -1) {
           currentThread->space->pcb->fd[i] = fdReturn;
           currentThread->space->pcb->byteRead[i] = 0;
           break;
        }
    }
    
    return i;
}

void doRead() {
    int virtAddr = machine->ReadRegister(4);
    int BufSize = machine->ReadRegister(5);
    int des = machine->ReadRegister(6);
    char * buf = new char[BufSize + 1];

    if (des == ConsoleInput){}
    else {
        OpenFile * o = openFileManager->openFileTable[currentThread->space->pcb->fd[des]].openFile;
        openFileManager->fileLock[currentThread->space->pcb->fd[des]]->Acquire();
        o->ReadAt(buf, BufSize, currentThread->space->pcb->byteRead[des]);
        openFileManager->fileLock[currentThread->space->pcb->fd[des]]->Release();
        buf[BufSize + 1] = '\0';
        for(int i = 0; i < BufSize; i++)
            machine->mainMemory[currentThread->space->Translate(virtAddr + i)] = buf[i];
        currentThread->space->pcb->byteRead[des] += BufSize;
    }
}

void doClose() {
    int closeId = machine->ReadRegister(4);
    int sysOpId = currentThread->space->pcb->fd[closeId];
    openFileManager->openFileTable[sysOpId].num--;
    if (openFileManager->openFileTable[sysOpId].num == 0) openFileManager->files->Clear(sysOpId);
    currentThread->space->pcb->fd[closeId] = -1;

}

//----------------------------------------------------------------------
// Helper function that either reads from main mem into a buffer or
// writes from a buffer into main mem.
//----------------------------------------------------------------------
 
 
int userReadWrite(int virtAddr, char* buffer, int size, int type) {
 
    int physAddr = 0;
    int numBytesFromPSLeft = 0;
    int numBytesCopied = 0;
    int numBytesToCopy = 0;
 
    if (type == USER_READ) { // from buffer to main memory
        while (size > 0) {
            physAddr = currentThread->space->Translate(virtAddr);
            numBytesFromPSLeft = PageSize - physAddr % PageSize;
            numBytesToCopy = (numBytesFromPSLeft < size) ? numBytesFromPSLeft : size;
            bcopy(buffer + numBytesCopied, machine->mainMemory + physAddr, numBytesToCopy);
            numBytesCopied += numBytesToCopy;
            size -= numBytesToCopy;
            virtAddr += numBytesToCopy;
        }
    }
    else if (type == USER_WRITE) { // from main memory to buffer
        while (size > 0) {
            physAddr = currentThread->space->Translate(virtAddr);
            numBytesFromPSLeft = PageSize - physAddr % PageSize;
            numBytesToCopy = (numBytesFromPSLeft < size) ? numBytesFromPSLeft : size;
            bcopy(machine->mainMemory + physAddr, buffer + numBytesCopied, numBytesToCopy);
            numBytesCopied += numBytesToCopy;
            size -= numBytesToCopy;
            virtAddr += numBytesToCopy;
        }
    }
    else {
        printf ("Invalid type passed in.\n");
        ASSERT(FALSE);
    }
    return numBytesCopied;
}


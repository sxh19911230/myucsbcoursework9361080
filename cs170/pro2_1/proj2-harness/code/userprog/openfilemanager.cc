// openfilemanager.cc
//

#include "openfilemanager.h"

//----------------------------------------------------------------------
// OpenFileManager::OpenFileManager
//  Construct and initialize the open file manager.
//----------------------------------------------------------------------

OpenFileManager::OpenFileManager()
{
   consoleWriteLock = new Lock("consoleWriteLock");
   fileLock = new Lock*[OPEN_FILE_TABLE_SIZE];
   for (int i = 0; i < OPEN_FILE_TABLE_SIZE; i++)
       fileLock[i] = new Lock("fileLock");
   files = new BitMap(OPEN_FILE_TABLE_SIZE);
}

//----------------------------------------------------------------------
// OpenFileManager::~OpenFileManager
//----------------------------------------------------------------------

OpenFileManager::~OpenFileManager()
{
    delete consoleWriteLock;
    for (int i = 0; i < OPEN_FILE_TABLE_SIZE; i++)
       delete fileLock[i];
    delete fileLock;
    delete files;
}

//----------------------------------------------------------------------
// OpenFileManager::addOpenFile
//  Adds an on open file to the system file table.
//----------------------------------------------------------------------

int OpenFileManager::addOpenFile(SysOpenFile openFile)
{
    int f = files->Find();
    openFileTable[f] = openFile;
    openFileTable[f].fileId = f;
    openFileTable[f].num = 0;
    return f;
}

//----------------------------------------------------------------------
// OpenFileManager::getOpenFile
//  Retrieves the system file table entry from the file table.
//----------------------------------------------------------------------

SysOpenFile *OpenFileManager::getOpenFile(int index)
{
    return &openFileTable[index];
}

void OpenFileManager::closeFile(int index) {
    files->Clear(index);
}


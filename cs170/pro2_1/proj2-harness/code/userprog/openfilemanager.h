// openfilemanager.h
//

#ifndef OPENFILEMANAGER_H
#define OPENFILEMANAGER_H

#include "sysopenfile.h"
#include "synch.h"

#define OPEN_FILE_TABLE_SIZE 32

class OpenFileManager {

public:
    OpenFileManager();
    ~OpenFileManager();

    int addOpenFile(SysOpenFile openFile);
    SysOpenFile *getOpenFile(int index);
    void closeFile(int index);

    Lock *consoleWriteLock;
    Lock **fileLock;

    SysOpenFile openFileTable[OPEN_FILE_TABLE_SIZE];
    BitMap *files;
};

#endif // OPENFILEMANAGER_H

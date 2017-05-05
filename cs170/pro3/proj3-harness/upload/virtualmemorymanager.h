/*
 * VirtualMemoryManager header
 *
 * Used to facilitate demand paging through providing a means by which page
 * faults can be handled and pages loaded from and stored to disk.
*/

#ifndef VIRTUAL_MEMORY_MANAGER_H
#define VIRTUAL_MEMORY_MANAGER_H

#include "bitmap.h"

class AddrSpace;
class TranslationEntry;

#define SWAP_SECTORS 512
#define SWAP_SECTOR_SIZE PageSize
#define SWAP_FILENAME "SWAP"

struct FrameInfo
{
    AddrSpace* space;
    int pageTableIndex;
};

struct SwapSectorInfo
{
    TranslationEntry* pageTableEntry;
    int swapFileIndex;
};

class VirtualMemoryManager
{
    public:
        VirtualMemoryManager();
        ~VirtualMemoryManager();

        int allocSwapSector();
        void deAllocSwapSector(int location);
        void writeToSwap(char *page, int pageSize, int backStoreLoc);
        void readFromSwap(char *page, int pageSize, int backStoreLoc);
        void swapPageIn(int virtAddr);
        void releasePages(AddrSpace* space);
        void copySwapSector(int to, int from);

        void loadPageToCurrVictim(int virtAddr);
        SwapSectorInfo *getSwapSectorInfo(int index);
        TranslationEntry* getPage(FrameInfo * pageInfo);

    private:
        BitMap *swapSectorMap;
        OpenFile *swapFile;
        FrameInfo *physicalMemoryInfo;
        SwapSectorInfo *swapSpaceInfo;
        int nextVictim; // global position into phys mem for FIFO w/ last-chance
};

#endif

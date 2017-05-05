/*
 * VirtualMemoryManager implementation
 *
 * Used to facilitate demand paging through providing a means by which page
 * faults can be handled and pages loaded from and stored to disk.
*/

#include <machine.h>
#include "virtualmemorymanager.h"
#include "system.h"

VirtualMemoryManager::VirtualMemoryManager()
{
    fileSystem->Create(SWAP_FILENAME, SWAP_SECTOR_SIZE * SWAP_SECTORS);
    swapFile = fileSystem->Open(SWAP_FILENAME);

    swapSectorMap = new BitMap(SWAP_SECTORS);
    physicalMemoryInfo = new FrameInfo[NumPhysPages];
    swapSpaceInfo = new SwapSectorInfo[SWAP_SECTORS];
    nextVictim = 0;
}

VirtualMemoryManager::~VirtualMemoryManager()
{
    fileSystem->Remove(SWAP_FILENAME);
    delete swapFile;
    delete [] physicalMemoryInfo;
    delete [] swapSpaceInfo;
}

int VirtualMemoryManager::allocSwapSector()
{
    int location = swapSectorMap->Find() * PageSize; // also marks the bit
    return location;
}

void VirtualMemoryManager::deAllocSwapSector(int location) {
    swapSectorMap->Clear(location / PageSize);
}

SwapSectorInfo * VirtualMemoryManager::getSwapSectorInfo(int index)
{
    return swapSpaceInfo + index;
}

void VirtualMemoryManager::writeToSwap(char *page, int pageSize,
                                       int backStoreLoc)
{
    swapFile->WriteAt(page, pageSize, backStoreLoc);
}

void VirtualMemoryManager::readFromSwap(char *page, int pageSize,
                                       int backStoreLoc)
{
    swapFile->ReadAt(page, pageSize, backStoreLoc);
}


/*
 * Use FIFO with 2nd chance to determine the victim frame
 */
void VirtualMemoryManager::swapPageIn(int virtAddr)
{
    TranslationEntry* currPage;
    bool waitingForFreeFrame = true;
    char buffer[PageSize];

    // TODO: use this while loop and the nextVictim variable to implement 2nd
    // chance page replacement

    while (waitingForFreeFrame)
    {
        FrameInfo *frameInfo = &physicalMemoryInfo[nextVictim];

        if (frameInfo->space == NULL) // nextVictim is a free frame
        {
            frameInfo->space = currentThread->space;

            frameInfo->pageTableIndex = virtAddr / PageSize;

            getPage(frameInfo)->valid = true;

            waitingForFreeFrame = false;
        }

        else // nextVictim is occupied by another page
        {
            currPage = getPage(frameInfo);

            // TODO: check the 'use' bit to implement the 2nd chance algorithm
            // page replacement algorithm

            if (currPage->use) currPage->use = 0;

            // TODO: check the 'dirty' bit and write this page back to the
            // swap file if necessary
            else {
                if (currPage->dirty) 
                   virtualMemoryManager->writeToSwap(
                       &machine->mainMemory[frameInfo->space->Translate(frameInfo->pageTableIndex * PageSize)],
                       PageSize, currPage->locationOnDisk);

                currPage->valid = false;

                frameInfo->space = currentThread->space;

                frameInfo->pageTableIndex = virtAddr / PageSize;

                getPage(frameInfo)->valid = true;

            // TODO: evict page currently occupying frame and swap the new
            // page in

                waitingForFreeFrame = false;
            }
        }
        nextVictim = (nextVictim + 1) % NumPhysPages;
    }

    // when we get here, "nextVictim" is in a good slot, and we have written
    // back anything necessary, so now loading the page is good to go
    loadPageToCurrVictim(virtAddr);
}

/*
 * Cleanup the physical memory allocated to a given address space after its
 * destructor invokes.
*/
void VirtualMemoryManager::releasePages(AddrSpace* space)
{
    // TODO: remove each page in the address space from the swap file and
    // clear its frame (if it is in memory) for re-allocation

    for (int i = 0; i < space->getNumPages(); i++)
    {
        TranslationEntry* currPage = space->getPage(i);

        // TODO: release page
        deAllocSwapSector(currPage->locationOnDisk);

    }
}

/*
 * After selecting a slot of physical memory as a victim and taking care of
 * synchronizing the data if needed, we load the faulting page into memory.
*/
void VirtualMemoryManager::loadPageToCurrVictim(int virtAddr)
{
    // TODO: load the page containing 'virtAddr' into the victim frame
    int pageTableIndex = virtAddr / PageSize;
    int thisVictim = nextVictim - 1;
    if (!nextVictim) thisVictim += NumPhysPages;
    TranslationEntry* page = currentThread->space->getPage(pageTableIndex);
    page->physicalPage = thisVictim;
    readFromSwap(&machine->mainMemory[thisVictim * PageSize], PageSize, page->locationOnDisk);
}

/*
 * Helper function for clock page replacement that retrieves the physical page
 * which corresponds to the given physical memory page information that the
 * VirtualMemoryManager maintains.
 */
TranslationEntry* VirtualMemoryManager::getPage(FrameInfo * physPageInfo)
{
    TranslationEntry* page = physPageInfo->space->getPage(physPageInfo->pageTableIndex);
    return page;
}

void VirtualMemoryManager::copySwapSector(int to, int from)
{
    char sectorBuf[SectorSize];
    swapFile->ReadAt(sectorBuf, SWAP_SECTOR_SIZE, from);
    swapFile->WriteAt(sectorBuf, SWAP_SECTOR_SIZE, to);
}

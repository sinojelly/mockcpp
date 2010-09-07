#include <stdlib.h>
#include <mockcpp/BlockAllocator.h>


MOCKCPP_NS_START


BlockAllocator::BlockAllocator(unsigned int blockSize, unsigned int blockNum)
    : sizeOfBlock(blockSize), numOfBlocks(blockNum), headOfFreeList(0)
{
    if(blockSize < sizeof(Block))
    {
        sizeOfBlock = sizeof(Block);
    }

    buffer = malloc(sizeOfBlock * blockNum);

    if ((void*)0 == buffer)
	{
        numOfBlocks = 0;
		return;
	}
    
    headOfFreeList = (Block *)buffer;
    Block* p = headOfFreeList; 
    for (unsigned int i = 1; i < blockNum; i++)
    {
        p->next = (Block *)((unsigned char*)buffer + i*sizeOfBlock);
        p = p->next;
    }

    p->next = 0;
}

BlockAllocator::~BlockAllocator()
{
    if (0 != buffer)
    {
        ::free(buffer);
        buffer = 0;
    }
    headOfFreeList = 0;
}

void* BlockAllocator::alloc(size_t size)
{
    if (0 == buffer)
	{
		return 0;
	}

    if (size > sizeOfBlock)
	{
		return 0;
	}
    
    if (0 == headOfFreeList)
    {
        return 0; 
    }
    
    void *ptr = (void *)headOfFreeList;
    headOfFreeList = headOfFreeList->next;

    return ptr;
}

bool BlockAllocator::misaligned(void* ptr) const
{
    return (((unsigned int)((char*)ptr - (char*)buffer)) % sizeOfBlock != 0);
}

bool BlockAllocator::outOfScope(void* ptr) const
{
    return  ptr < buffer 
         || ptr >= (void*)((char*)buffer + numOfBlocks*sizeOfBlock);
}

bool BlockAllocator::hasBeenFreed(void* ptr) const
{
    for(Block* p = headOfFreeList; p != 0; p = p->next)
    {
        if((void*)p == ptr)
        {
            return true;
        }
    }

    return false;
}

bool BlockAllocator::isBadBlock(void* ptr) const
{
    return outOfScope(ptr) || misaligned(ptr) ||  hasBeenFreed(ptr);
}

void BlockAllocator::free(void* ptr)
{
    if (0 == ptr)
    {
        return;
    }

    if (isBadBlock(ptr))
	{
		return;
	}
    
    ((Block *)ptr)->next = headOfFreeList;
    headOfFreeList = (Block *)ptr;
}

MOCKCPP_NS_END


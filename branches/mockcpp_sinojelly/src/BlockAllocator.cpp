/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
	                      <Chen Guodong: sinojelly@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#include <stdlib.h>
#include <mockcpp/BlockAllocator.h>
#include <mockcpp/PageAllocator.h>

USING_MOCKCPP_NS

MOCKCPP_NS_START

// specify the number of blocks
BlockAllocator::BlockAllocator(unsigned int blockSize, unsigned int blockNum)
    : sizeOfBlock(blockSize), numOfBlocks(blockNum), pageAllocator(0), headOfFreeList(0)
	, sizeOfPool(0), numOfPool(0)
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

// specify the pool allocator
BlockAllocator::BlockAllocator(unsigned int blockSize, PageAllocator *allocator)
	: sizeOfBlock(blockSize), numOfBlocks(0), pageAllocator(allocator), headOfFreeList(0)
	, sizeOfPool(0), numOfPool(0)
{
	if(blockSize < sizeof(Block))
	{
		sizeOfBlock = sizeof(Block);
	}

	buffer = allocator->alloc(0); // specify size 0 to allocate a large page memory.

	if ((void*)0 == buffer)
	{
		numOfBlocks = 0;
		return;
	}

	numOfBlocks = allocator->pageSize() / blockSize;

	headOfFreeList = (Block *)buffer;
	Block* p = headOfFreeList; 
	for (unsigned int i = 1; i < numOfBlocks; i++)
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
		if (pageAllocator != 0)
		{
			pageAllocator->free(buffer);
		}
        else 
		{
			::free(buffer);
		}
        
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

bool BlockAllocator::freeable(void* ptr)
{
    if (0 == ptr)
    {
        return true;
    }
	
    return !isBadBlock(ptr);
}


MOCKCPP_NS_END


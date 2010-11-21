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
#include <new>

#include <mockcpp/AllocatorContainer.h>
#include <mockcpp/BlockAllocator.h>


MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////
void AllocatorContainer::free(void* ptr)
{
    ALLOCATOR_NODE *p;
    APR_RING_FOREACH(p, allocators, ALLOCATOR_NODE, link)
    {
        if (p->allocator->freeable(ptr))
        {
            p->allocator->free(ptr);
            return;
        }    
    }
}

/////////////////////////////////////////////////////////////////
void *AllocatorContainer::alloc(size_t size)
{
    if (size > blockSize)
    {
        return 0;
    }
    
    void *temp = 0; 
    ALLOCATOR_NODE *p;
    APR_RING_FOREACH(p, allocators, ALLOCATOR_NODE, link)
    {
        temp = p->allocator->alloc(size);
        if (temp != 0)
        {
            return temp;
        }    
    }

    BlockAllocator* allocator = addAllocator();
    
    return allocator->alloc(size);
}

/////////////////////////////////////////////////////////////////
BlockAllocator* AllocatorContainer::addAllocator()
{
    void *temp = malloc(sizeof(BlockAllocator));

    // use placement new to avoid mem_checker failure.
    BlockAllocator *tempAllocator = new (temp)BlockAllocator(blockSize, pageAllocator);

    ALLOCATOR_NODE *p = (ALLOCATOR_NODE *)malloc(sizeof(ALLOCATOR_NODE));
    p->allocator = tempAllocator;
    
    APR_RING_INSERT_TAIL(allocators, p, ALLOCATOR_NODE, link);

    return tempAllocator;
}

/////////////////////////////////////////////////////////////////
void AllocatorContainer::initialize(size_t _blockSize, PageAllocator *_pageAllocator)
{
    if (allocators != 0)
    {
        return;
    }

    allocators = (ALLOCATOR_NODES *)malloc(sizeof(ALLOCATOR_NODES));
    APR_RING_INIT(allocators, ALLOCATOR_NODE, link);

    blockSize = _blockSize;
    pageAllocator = _pageAllocator->clone();

    (void)addAllocator();
}

/////////////////////////////////////////////////////////////////
AllocatorContainer::~AllocatorContainer()
{
	if (allocators == 0)
    {
        return;
    }
	
    ALLOCATOR_NODE *p;
    
	while (!APR_RING_EMPTY(allocators, ALLOCATOR_NODE, link))
	{
		p = APR_RING_FIRST(allocators);
		APR_RING_REMOVE(p, link);
        p->allocator->~BlockAllocator();
        ::free(p->allocator); 
        ::free(p); 
	}

	free(allocators);
    pageAllocator->destoryClone();
    
    allocators = 0;
}

/////////////////////////////////////////////////////////////////


MOCKCPP_NS_END


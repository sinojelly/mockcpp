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

#include <mockcpp/AllocatorContainer.h>
#include <mockcpp/BlockAllocator.h>


MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////
void AllocatorContainer::free(void* ptr)
{
    std::list<BlockAllocator*>::iterator it;

    for (it = allocators.begin(); it != allocators.end(); ++it)
    {
        if ((*it)->freeable(ptr))
        {
           (*it)->free(ptr);
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
    std::list<BlockAllocator*>::iterator it;

    for (it = allocators.begin(); it != allocators.end(); ++it)
    {
        temp = (*it)->alloc(size);
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
        
    allocators.push_back(tempAllocator);

    return tempAllocator;
}

/////////////////////////////////////////////////////////////////
void AllocatorContainer::initialize(size_t _blockSize, PageAllocator *_pageAllocator)
{
    if (allocators.size() > 0)
    {
        return;
    }

    blockSize = _blockSize;
    pageAllocator = _pageAllocator;

    (void)addAllocator();
}

/////////////////////////////////////////////////////////////////
AllocatorContainer::~AllocatorContainer()
{
    std::list<BlockAllocator*>::iterator it;

    for (it = allocators.begin(); it != allocators.end(); ++it)
    {
        (*it)->~BlockAllocator();
        ::free(*it);
    }

    allocators.clear();
}

/////////////////////////////////////////////////////////////////


MOCKCPP_NS_END


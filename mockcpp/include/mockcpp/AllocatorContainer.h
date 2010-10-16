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

#ifndef __MOCKCPP_ALLOCATORCONTAINER_H__
#define __MOCKCPP_ALLOCATORCONTAINER_H__

#include <mockcpp/MemAllocator.h>

// if use vector or list, mem checker will detect a memory leak after a testcase run finished, 
// so use apr_ring, it use malloc, not new, mem check will not report failures.
#include <mockcpp/apr_ring.h>

MOCKCPP_NS_START

struct PageAllocator;
struct BlockAllocator;


struct AllocatorContainer : public MemAllocator
{
    AllocatorContainer(){}
    ~AllocatorContainer();
    
    void initialize(size_t blockSize, PageAllocator *_pageAllocator);

    void* alloc(size_t size);
    void free(void* ptr);

private:
    BlockAllocator* addAllocator();  


private:
	struct ALLOCATOR_NODE
	{
		APR_RING_ENTRY(ALLOCATOR_NODE) link;
		BlockAllocator* allocator;
	};
	APR_RING_HEAD(ALLOCATOR_NODES, ALLOCATOR_NODE);
	ALLOCATOR_NODES *allocators;

private:
    size_t blockSize;
    PageAllocator *pageAllocator;
};



MOCKCPP_NS_END

#endif


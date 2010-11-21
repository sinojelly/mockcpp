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
#include <mockcpp/Linux32ProtectPageAllocator.h>
#include <string.h>
#include <sys/mman.h>
#include <new>

MOCKCPP_NS_START

Linux32ProtectPageAllocator::Linux32ProtectPageAllocator(PageAllocator *pageAllocator)
	: allocator(pageAllocator), cloneObject(0)
{
}

Linux32ProtectPageAllocator::~Linux32ProtectPageAllocator()
{
    delete allocator;
}

void* Linux32ProtectPageAllocator::alloc(size_t size)
{
	void *pages = allocator->alloc(size);

	if (pages == NULL)
	{
		return NULL;
	}

	if (mprotect(allocator->align(pages) , 2 * pageSize(), PROT_EXEC|PROT_WRITE|PROT_READ) != 0)
	{
		allocator->free(pages);
		return NULL;
	}

	return pages;
}

void Linux32ProtectPageAllocator::free(void* ptr)
{
	allocator->free(ptr);
}

size_t Linux32ProtectPageAllocator::pageSize()
{
	return allocator->pageSize();
}

PageAllocator *Linux32ProtectPageAllocator::clone()
{
    void *addr = ::malloc(sizeof(Linux32ProtectPageAllocator));
    Linux32ProtectPageAllocator *object = new (addr) Linux32ProtectPageAllocator(allocator->clone());
    object->cloneObject = object; // save for destorying
    return object;
}

void Linux32ProtectPageAllocator::destoryClone()
{
    if (cloneObject != 0)
    {
        allocator->destoryClone(); // allocator must be cloned too, and this alway ok, because in clone, it called allocator->clone().    
        ::free(cloneObject);
        cloneObject = 0;
    }
}


MOCKCPP_NS_END


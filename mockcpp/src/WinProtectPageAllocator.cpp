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

#ifdef _MSC_VER

#include <Windows.h>
#include <mockcpp/WinProtectPageAllocator.h>
#include <new>

MOCKCPP_NS_START

WinProtectPageAllocator::WinProtectPageAllocator(PageAllocator *pageAllocator)
	: allocator(pageAllocator), cloneObject(0)
{
}

WinProtectPageAllocator::~WinProtectPageAllocator()
{
    delete allocator;
}

void* WinProtectPageAllocator::alloc(size_t size)
{

	LPVOID pages = allocator->alloc(size);

	if (pages == NULL)
	{
		return NULL;
	}

	DWORD oldProtect;
	if (VirtualProtect( pages, pageSize(), PAGE_EXECUTE_READWRITE, &oldProtect) == 0)
	{
		allocator->free(pages);
		return NULL;
	}

	return pages;
}

void WinProtectPageAllocator::free(void* ptr)
{
	// TODO: should i VirtualProtect here?
	allocator->free(ptr);
}

size_t WinProtectPageAllocator::pageSize()
{
	return allocator->pageSize();
}

PageAllocator *WinProtectPageAllocator::clone()
{
    void *addr = ::malloc(sizeof(WinProtectPageAllocator));
    WinProtectPageAllocator *object = new (addr) WinProtectPageAllocator(allocator->clone());
    object->cloneObject = object; // save for destorying
    return object;
}

void WinProtectPageAllocator::destoryClone()
{
    if (cloneObject != 0)
    {
        allocator->destoryClone(); // allocator must be cloned too, and this alway ok, because in clone, it called allocator->clone().
        ::free(cloneObject);
        cloneObject = 0;
    }
}


MOCKCPP_NS_END

#endif


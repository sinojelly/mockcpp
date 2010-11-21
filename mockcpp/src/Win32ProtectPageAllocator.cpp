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
#include <mockcpp/Win32ProtectPageAllocator.h>
#include <new>

MOCKCPP_NS_START

Win32ProtectPageAllocator::Win32ProtectPageAllocator(PageAllocator *pageAllocator)
	: allocator(pageAllocator), cloneObject(0)
{
}

Win32ProtectPageAllocator::~Win32ProtectPageAllocator()
{
    delete allocator;
}

void* Win32ProtectPageAllocator::alloc(size_t size)
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

void Win32ProtectPageAllocator::free(void* ptr)
{
	// TODO: should i VirtualProtect here?
	allocator->free(ptr);
}

size_t Win32ProtectPageAllocator::pageSize()
{
	return allocator->pageSize();
}

PageAllocator *Win32ProtectPageAllocator::clone()
{
    void *addr = ::malloc(sizeof(Win32ProtectPageAllocator));
    Win32ProtectPageAllocator *object = new (addr) Win32ProtectPageAllocator(allocator->clone());
    object->cloneObject = object; // save for destorying
    return object;
}

void Win32ProtectPageAllocator::destoryClone()
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


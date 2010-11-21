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
#include <mockcpp/Win32PageAllocator.h>
#include <new>

MOCKCPP_NS_START

#define PAGE_SIZE    ( 64 * 1024)

Win32PageAllocator::Win32PageAllocator()
	: sizeOfPage(0), cloneAddr(0)
{
}

Win32PageAllocator::~Win32PageAllocator()
{
}

void* Win32PageAllocator::alloc(size_t size)
{
	sizeOfPage = (size <= PAGE_SIZE) ? PAGE_SIZE : size;
	return ::VirtualAlloc(NULL, sizeOfPage, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE );
}

void Win32PageAllocator::free(void* ptr)
{
	::VirtualFree(ptr, 0, MEM_RELEASE | MEM_DECOMMIT);
}

size_t Win32PageAllocator::pageSize()
{
	return sizeOfPage;
}

PageAllocator *Win32PageAllocator::clone()
{
    cloneAddr = malloc(sizeof(Win32PageAllocator));
    Win32PageAllocator *cloneObject = new (cloneAddr) Win32PageAllocator;
    cloneObject->cloneAddr = cloneAddr; // save for destorying
    return cloneObject;
}

void Win32PageAllocator::destoryClone()
{
    if (cloneAddr != 0)
    {
        ::free(cloneAddr);
        cloneAddr = 0;
    }
}

MOCKCPP_NS_END

#endif

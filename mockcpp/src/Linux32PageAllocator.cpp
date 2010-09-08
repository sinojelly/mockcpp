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
#include <mockcpp/Linux32PageAllocator.h>

#include <limits.h>
#ifndef PAGESIZE
#define PAGESIZE   4096
#endif

MOCKCPP_NS_START


Linux32PageAllocator::Linux32PageAllocator()
	: sizeOfPage(0)
{
}

void* Linux32PageAllocator::alloc(size_t size)
{
	sizeOfPage = (size <= PAGESIZE) ? PAGESIZE : size;
	return ::malloc(sizeOfPage);
}

void Linux32PageAllocator::free(void* ptr)
{
	::free(ptr);
}

size_t Linux32PageAllocator::pageSize()
{
	return sizeOfPage;
}

MOCKCPP_NS_END



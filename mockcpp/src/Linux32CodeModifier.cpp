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

#include <string.h>
#include <sys/mman.h>
#include <mockcpp/Linux32CodeModifier.h>
#include <mockcpp/PageAllocator.h>


MOCKCPP_NS_START


Linux32CodeModifier::Linux32CodeModifier(PageAllocator *pageAllocator)
	: page(pageAllocator->clone())
{
}

Linux32CodeModifier::~Linux32CodeModifier()
{
    page->destoryClone();
}

bool Linux32CodeModifier::modify(void *dest, void *src, size_t size)
{
	if (mprotect(page->align(dest) , 2 * page->pageSize(), PROT_EXEC|PROT_WRITE|PROT_READ) != 0)
	{
		return false;
	}

	//(void)memcpy(dest, src, size); // something wrong on linux: after memcpy(or 5 single byte copy),  the 4 bytes following jmp, src is 0x07c951b0, but dest is 0x07b851b0. so use unsigned int *, it works ok.
	*((unsigned char *)dest) = *((unsigned char *)src);
	*((unsigned int *)((unsigned int)dest + 1)) = *((unsigned int *)((unsigned int)src + 1));

	return true;
}


MOCKCPP_NS_END



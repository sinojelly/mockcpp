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

#include <mockcpp/CApiHook.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Linux32PageAllocator.h>
#include <mockcpp/Linux32ProtectPageAllocator.h>
#include <mockcpp/Linux32CodeModifier.h>
#include <mockcpp/BlockAllocator.h>
#include <mockcpp/Arch32ApiHook.h>

MOCKCPP_NS_START


/////////////////////////////////////////////////////////////////
CApiHook::CApiHook(ApiHook::Address pfnOld, ApiHook::Address pfnNew)
   : allocator(new Linux32ProtectPageAllocator(new Linux32PageAllocator)), hooker(new Arch32ApiHook(allocator, new Linux32CodeModifier(allocator)))
{
	hooker->hook(pfnOld, pfnNew);
}

/////////////////////////////////////////////////////////////////
CApiHook::~CApiHook()
{
	delete hooker;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


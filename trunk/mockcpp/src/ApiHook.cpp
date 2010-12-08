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
#include <inttypes.h>

#include "JmpOnlyApiHook.h"
#include <mockcpp/ApiHook.h>
#include <mockcpp/JmpCode.h>
#include <mockcpp/PageAllocator.h>

MOCKCPP_NS_START

#define ZERO_ADDR 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

const unsigned char thunkTemplate[] = 
{
    0x48, 0xBF, ZERO_ADDR,   // mov rdi, api
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, ZERO_ADDR // jmp stub
};

struct ThunkCode
{
   static void copyTo(void* thunk, const void* api, const void* stub)
   {
      ::memcpy(thunk, thunkTemplate, sizeof(thunkTemplate));
      *(uintptr_t*)((unsigned char*)thunk+2) = (uintptr_t)api;
      *(uintptr_t*)((unsigned char*)thunk+16) = (uintptr_t)stub;
   }

   static size_t size()
   { return sizeof(thunkTemplate); }
};


////////////////////////////////////////////////////////
struct ApiHookImpl
{
   /////////////////////////////////////////////////////
   ApiHookImpl( const void* api
              , const void* stub
              , const void* stubConverter
              , const void* realStub)
      : stubHook(api, stub)
   {
       thunk = PageAllocator::alloc(ThunkCode::size(), thunkSize);
       ThunkCode::copyTo(thunk, api, realStub);
       converterHook = new JmpOnlyApiHook(stubConverter, thunk);
   }

   /////////////////////////////////////////////////////
   ~ApiHookImpl()
   {
       PageAllocator::free(thunk, thunkSize);
       delete converterHook;
   }

   /////////////////////////////////////////////////////
   JmpOnlyApiHook stubHook;
   JmpOnlyApiHook* converterHook;
   size_t  thunkSize;
   void*   thunk;
};

/////////////////////////////////////////////////////////////////
ApiHook::ApiHook 
              ( const void* api 
              , const void* stub
              , const void* stubConverter
              , const void* realStub)
	: This(new ApiHookImpl(api, stub, stubConverter, realStub))
{
}

/////////////////////////////////////////////////////////////////
ApiHook::~ApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


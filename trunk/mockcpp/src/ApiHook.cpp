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
#include "ThunkCode.h"
#include <mockcpp/ApiHook.h>
#include <mockcpp/JmpCode.h>
#include <mockcpp/PageAllocator.h>
#include <mockcpp/Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
struct ApiHookImpl
{
   /////////////////////////////////////////////////////
   ApiHookImpl( const void* api
              , const void* stub
              , const void* stubConverter
              , const void* realStub)
   {
       thunk = PageAllocator::alloc(ThunkCode::size(), thunkSize);
       MOCKCPP_ASSERT_FALSE_MESSAGE
              ( "allocate memory for thunk code failed"
              , thunk == 0);

       ThunkCode::copyTo(thunk, api, realStub);
       converterHook = new JmpOnlyApiHook(stubConverter, thunk);
       stubHook = new JmpOnlyApiHook(api, stub);
   }

   /////////////////////////////////////////////////////
   ~ApiHookImpl()
   {
       PageAllocator::free(thunk, thunkSize);
       delete converterHook;
       delete stubHook;
   }

   /////////////////////////////////////////////////////
   JmpOnlyApiHook* stubHook;
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


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

#include "JmpOnlyApiHook.h"
#include <mockcpp/ApiHook.h>
#include <mockcpp/JmpCode.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
struct ApiHookImpl
{
   /////////////////////////////////////////////////////
   ApiHookImpl( const void* api
              , const void* stub
              , const void* stubConverter
              , const void* realStub)
      : stubHook(api, stub)
      , converterHook(stubConverter, realStub)
   {
   }

   /////////////////////////////////////////////////////
   ~ApiHookImpl()
   {
   }

   /////////////////////////////////////////////////////
   JmpOnlyApiHook stubHook;
   JmpOnlyApiHook converterHook;
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


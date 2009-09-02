/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

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

#include <iostream>
#include <mockcpp/DestructorChecker.h>
#include <mockcpp/MethodInfoReader.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/VirtualTableUtils.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////////////////
namespace
{
   struct DummyType {};

   const unsigned int invalidIndex = 0xFFFFFFFF;

   unsigned int indexOfVPTR;
   unsigned int indexOfVTBL;

   bool initialized = false;

   void** vtbl = createVtbls(MOCKCPP_MAX_INHERITANCE);
}

////////////////////////////////////////////////////////////////////////
template <int IndexOfVptr, int IndexOfVtbl, typename T>
struct DestructorChecker
{
   void check(void*)
   {
      indexOfVPTR = IndexOfVptr;
      indexOfVTBL = IndexOfVtbl;
   }
};

///////////////////////////////////////////////////////////////////////
#define MOCKCPP_SET_DESTRUCTOR_CHECKER_VTBL(I, J) do{ \
   vtbl[getRealVtblIndex(I,J)] = getAddrOfMethod(&DestructorChecker<I,J,DummyType>::check); \
}while(0)

static void initialize()
{
   indexOfVPTR = invalidIndex;
   indexOfVTBL = invalidIndex;

   if(initialized)
   {
      return;
   } 



   #include <mockcpp/DestructorCheckerDef.h>

   initialized = true;
}

namespace
{
   struct FakeObject
   {
      void* vptr[MOCKCPP_MAX_INHERITANCE];
   };
};


///////////////////////////////////////////////////////////////////////
void* createDestructorChecker(const std::type_info& info)
{
   initialize();
   
   FakeObject* object = new FakeObject();

   initializeVtbls(object->vptr, vtbl, MOCKCPP_MAX_INHERITANCE,info, false);

   return (void*)object;
}

///////////////////////////////////////////////////////////////////////
#define MOCKCPP_THROW_NO_PURE_VIRTUAL_EXCEPTION() do { \
   MOCKCPP_FAIL("You are trying to mock a non-pure-virtual object"); \
} while(0)

///////////////////////////////////////////////////////////////////////
unsigned int getIndexOfVptrOfDestructor()
{
   if(indexOfVPTR == invalidIndex)
   {
      MOCKCPP_THROW_NO_PURE_VIRTUAL_EXCEPTION();
   }

   return indexOfVPTR;
}

///////////////////////////////////////////////////////////////////////
unsigned int getIndexOfVtblOfDestructor()
{
   if(indexOfVPTR == invalidIndex)
   {
      MOCKCPP_THROW_NO_PURE_VIRTUAL_EXCEPTION();
   }

   return indexOfVTBL;
}

///////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


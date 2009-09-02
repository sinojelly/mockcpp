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

namespace
{
   struct FakeObject
   {
      void* vptr[MOCKCPP_MAX_INHERITANCE];
   };

   FakeObject* object = new FakeObject();

   template <int IndexOfVptr, int IndexOfVtbl, typename T>
   struct MethodIndexChecker
   {
      void check()
      {
         indexOfVPTR = IndexOfVptr;
         indexOfVTBL = IndexOfVtbl;
      }
   };

};
///////////////////////////////////////////////////////////////////////
#define MOCKCPP_SET_GENERIC_METHOD_CHECKER_VTBL(I, J) do{ \
   vtbl[getRealVtblIndex(I,J)] = getAddrOfMethod(&MethodIndexChecker<I,J,DummyType>::check); \
}while(0)

static void initialize()
{
   indexOfVPTR = invalidIndex;
   indexOfVTBL = invalidIndex;

   if(initialized)
   {
      return;
   } 

   #include <mockcpp/GenericMethodCheckerDef.h>

   initialized = true;
}

///////////////////////////////////////////////////////////////////////
void* createMethodInfoChecker(const std::type_info& info)
{
   initialize();
   
   initializeVtbls(object->vptr, vtbl, MOCKCPP_MAX_INHERITANCE,info, false);

   return (void*)object;
}

///////////////////////////////////////////////////////////////////////
#define MOCKCPP_THROW_NO_PURE_VIRTUAL_EXCEPTION() do { \
   MOCKCPP_FAIL("You are trying to mock a non-pure-virtual object"); \
} while(0)

///////////////////////////////////////////////////////////////////////
unsigned int getIndexOfVptrOfMethod()
{
   if(indexOfVPTR == invalidIndex)
   {
      MOCKCPP_THROW_NO_PURE_VIRTUAL_EXCEPTION();
   }

   return indexOfVPTR;
}

///////////////////////////////////////////////////////////////////////
unsigned int getIndexOfVtblOfMethod()
{
   if(indexOfVPTR == invalidIndex)
   {
      MOCKCPP_THROW_NO_PURE_VIRTUAL_EXCEPTION();
   }

   return indexOfVTBL;
}

///////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


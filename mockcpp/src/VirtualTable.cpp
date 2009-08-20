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

#include <typeinfo>

#include <mockcpp/VirtualTable.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/MethodInfoReader.h>


MOCKCPP_NS_START

struct VirtualTableImpl
{
	VirtualTableImpl( IndexInvokableGetter* getter
                   , unsigned int numberOfVptr
                   , const std::type_info& info);
   ~VirtualTableImpl();

   void validateNumberOfVptr();
   void validateIndexOfVtbl(unsigned int index);
   void validateIndexOfVptr(unsigned int index);
   void validateVptr(void** vptr);

   void reset();

   void** vtbl;
   void* vptr[MOCKCPP_MAX_INHERITANCE+1];
   unsigned int numberOfVptr;
   IndexInvokableGetter* indexInvokableGetter;
};

/////////////////////////////////////////////////////////////////
namespace
{
   struct DefaultMethodHolder
   {
      void method()
      {
         MOCKCPP_FAIL("The method you are invoking is not specified by mocker."); 
      }
   };
}

/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateVptr(void** pVptr)
{
   MOCKCPP_ASSERT_TRUE_MESSAGE(
     PACKAGE " internal error(1018). please report this bug to " PACKAGE_BUGREPORT ".",
     pVptr == vptr);
}
/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateNumberOfVptr()
{
   oss_t oss;

   oss << "Seems that the interface you are trying to mock "
       << "inherites from too many base classes (" 
       << numberOfVptr 
       << "), or it's not a pure virtual class. "
       << "Here are some hints for you: \n"
       << "1. " PACKAGE " only supports mocking pure virtual class; \n"
       << "2. you can change the MOCKCPP_MAX_INHERITANCE setting to maximun 7, then rebuild " PACKAGE "; \n"
       << "3. you can refine your design to make it simpler.";

   MOCKCPP_ASSERT_TRUE_MESSAGE(
      oss.str(), 
      numberOfVptr <= MOCKCPP_MAX_INHERITANCE);
}
/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateIndexOfVtbl(unsigned int index)
{
   oss_t oss;

   oss << "Did you define too many methods in an interface? "
       << "Probably you should refine your design, "
       << "or you can reconfig MOCKCPP_MAX_VTBL_SIZE bigger, "
       << "it's current setting is " 
       << MOCKCPP_MAX_VTBL_SIZE 
       << ", the biggest value it could be set is 50. "
       << "FYI: the index of method which you are trying to mock is "
       << index + 1 << ".";

   MOCKCPP_ASSERT_TRUE_MESSAGE(
      oss.str(), 
      index < MOCKCPP_MAX_VTBL_SIZE);
}
/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::validateIndexOfVptr(unsigned int index)
{
   MOCKCPP_ASSERT_TRUE_MESSAGE(
      PACKAGE " internal error. please report it to " PACKAGE_BUGREPORT ".",
      index < numberOfVptr);
}

/////////////////////////////////////////////////////////////////
void
VirtualTableImpl::reset()
{
   void * defaultMethodAddr = getAddrOfMethod(&DefaultMethodHolder::method);
   for(unsigned index = 0; index < numberOfVptr; index++)
   {
      for(unsigned int i=2; i<MOCKCPP_MAX_VTBL_SIZE+2; i++)
      {
         vtbl[index*(MOCKCPP_MAX_VTBL_SIZE+2)+i] = defaultMethodAddr;
      }
   }
}

/////////////////////////////////////////////////////////////////
VirtualTableImpl::VirtualTableImpl(IndexInvokableGetter* getter
     , unsigned int numberOfVPTR, const std::type_info& refTypeInfo)
     : numberOfVptr(numberOfVPTR), indexInvokableGetter(getter)
{
   if(numberOfVptr == 0)
   {
      numberOfVptr = 1;
   }

   validateNumberOfVptr();

   // 1 for pointer to typeinfo && offset
   vtbl = new void*[numberOfVptr*(MOCKCPP_MAX_VTBL_SIZE+2)];
   
   for(unsigned int i=0; i<numberOfVptr; i++)
   {
      vtbl[i*(MOCKCPP_MAX_VTBL_SIZE+2)+0] = (void*)(-1*(sizeof(void*)*i));
      vtbl[i*(MOCKCPP_MAX_VTBL_SIZE+2)+1] = (void*)&refTypeInfo;
      vptr[i] = &vtbl[i*(MOCKCPP_MAX_VTBL_SIZE+2)+2];
   }

   vptr[MOCKCPP_MAX_INHERITANCE] = (void*)this;

   reset();
}

/////////////////////////////////////////////////////////////////
VirtualTableImpl::~VirtualTableImpl()
{
    delete [] vtbl;
}

/////////////////////////////////////////////////////////////////
VirtualTable::VirtualTable(IndexInvokableGetter* getter
    , unsigned int numberOfVptr, const std::type_info& info)
    : This(new VirtualTableImpl(getter, numberOfVptr, info))
{}

/////////////////////////////////////////////////////////////////
VirtualTable::~VirtualTable()
{ delete This; }

/////////////////////////////////////////////////////////////////
void*
VirtualTable::toPointerToInterface() const
{
    return (void*)&(This->vptr[0]);
}
 
/////////////////////////////////////////////////////////////////
void
VirtualTable::addMethod(void* methodAddr, unsigned int indexOfVtbl, unsigned int indexOfVptr)
{
    This->validateIndexOfVtbl(indexOfVtbl);
    This->validateIndexOfVptr(indexOfVptr);

    This->vtbl[(indexOfVptr*(MOCKCPP_MAX_VTBL_SIZE+2)) + indexOfVtbl+2] = methodAddr;
}

/////////////////////////////////////////////////////////////////
void
VirtualTable::reset()
{
    This->reset();
}

/////////////////////////////////////////////////////////////////
IndexInvokableGetter*
VirtualTable::getInvokableGetter(void* caller, unsigned int vptrIndex)
{
   void** vptr = &((void**)caller)[-(int)vptrIndex];

   VirtualTableImpl* pThis = (VirtualTableImpl*)vptr[MOCKCPP_MAX_INHERITANCE];

   pThis->validateVptr(vptr);
   
   return pThis->indexInvokableGetter;
}

MOCKCPP_NS_END

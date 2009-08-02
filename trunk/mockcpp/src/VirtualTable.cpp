
#include <VirtualTable.h>
#include <Asserter.h>
#include <OutputStringStream.h>
#include <MethodInfoReader.h>


MOCKCPP_NS_START

struct VirtualTableImpl
{

	VirtualTableImpl(IndexInvokableGetter* getter, unsigned int numberOfVptr);
   ~VirtualTableImpl();

   void validateNumberOfVptr();
   void validateIndexOfVtbl(unsigned int index);
   void validateIndexOfVptr(unsigned int index);
   void validateVptr(void** vptr);

   void** vtbl;
   void* vptr[MOCKCPP_MAX_INHERITANCE+1];
   unsigned int numberOfVptr;
   IndexInvokableGetter* indexInvokableGetter;
};

/////////////////////////////////////////////////////////////////
namespace {
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
     "mockcpp internal error(1018). please report this bug to darwin.yuan@gmail.com",
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
       << "1. mockcpp only supports mocking pure virtual class; \n"
       << "2. you can change the MOCKCPP_MAX_INHERITANCE setting to maximun 7, then rebuild mockcpp; \n"
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
       << "or you can reconfig mockcpp MOCKCPP_MAX_VTBL_SIZE bigger, "
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
      "mockcpp internal error. please report it to darwin.yuan@gmail.com.",
      index < numberOfVptr);
}
/////////////////////////////////////////////////////////////////
VirtualTableImpl::VirtualTableImpl(IndexInvokableGetter* getter
     , unsigned int numberOfVPTR)
     : numberOfVptr(numberOfVPTR), indexInvokableGetter(getter)
{
   if(numberOfVptr == 0)
   {
      numberOfVptr = 1;
   }

   validateNumberOfVptr();

   vtbl = new void*[numberOfVptr*MOCKCPP_MAX_VTBL_SIZE];
   
   for(unsigned int i=0; i<numberOfVptr; i++)
   {
      vptr[i] = &vtbl[i*MOCKCPP_MAX_VTBL_SIZE];
   }

   void * defaultMethodAddr = getAddrOfMethod(&DefaultMethodHolder::method);
   for(unsigned int i=0; i<numberOfVptr*MOCKCPP_MAX_VTBL_SIZE; i++)
   {
      vtbl[i] = defaultMethodAddr;
   }

   vptr[MOCKCPP_MAX_INHERITANCE] = (void*)this;
}

/////////////////////////////////////////////////////////////////
VirtualTableImpl::~VirtualTableImpl()
{
    delete [] vtbl;
}

/////////////////////////////////////////////////////////////////
VirtualTable::VirtualTable(IndexInvokableGetter* getter, unsigned int numberOfVptr)
    : This(new VirtualTableImpl(getter, numberOfVptr))
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

    This->vtbl[indexOfVptr*MOCKCPP_MAX_VTBL_SIZE + indexOfVtbl] = methodAddr;
}

/////////////////////////////////////////////////////////////////
IndexInvokableGetter*
VirtualTable::getInvokableGetter(void* caller, unsigned int vptrIndex)
{
   void** vptr = &((void**)caller)[-vptrIndex];

   VirtualTableImpl* pThis = (VirtualTableImpl*)vptr[MOCKCPP_MAX_INHERITANCE];

   pThis->validateVptr(vptr);
   
   return pThis->indexInvokableGetter;
}

MOCKCPP_NS_END


#ifndef __MOCKCPP_MOCK_OBJECT_BASE_H
#define __MOCKCPP_MOCK_OBJECT_BASE_H

#include <mockcpp.h>
#include <ChainableMockObjectBase.h>
#include <InvocationMockBuilderGetter.h>

MOCKCPP_NS_START

struct MockObjectBaseImpl;

struct MockObjectBase : public ChainableMockObjectBase
{
   MockObjectBase(const std::string& objName, unsigned int numberOfVptr = 1);

   ~MockObjectBase();

   void reset();

protected:

   InvocationMockBuilderGetter
   createInvocationMockerBuilderGetter(const std::string& name, \
          void* addr, unsigned int vptrIndex, unsigned int vtblIndex);
   
   void* toPointerToInterface() const;

private:

   MockObjectBaseImpl* This;
};

MOCKCPP_NS_END

#endif


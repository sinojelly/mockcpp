
#include <MockObjectBase.h>
#include <IndexInvokableGetter.h>
#include <Invokable.h>
#include <VirtualTable.h>
#include <ChainableMockMethodCore.h>
#include <ChainableMockMethodIndexKey.h>
#include <ChainableMockMethodContainer.h>
#include <InvocationMockBuilderGetter.h>

MOCKCPP_NS_START

struct MockObjectBaseImpl : public IndexInvokableGetter
{
   MockObjectBaseImpl(unsigned int numberOfVptr, ChainableMockMethodContainer* c);
   ~MockObjectBaseImpl();

   Invokable* getInvokable(unsigned int vptrIndex, unsigned int vtblIndex) const;

   ChainableMockMethodCore*
   getMethod(const std::string& name, void* addr, \
             unsigned int vptrIndex, unsigned int vtblIndex, \
             InvocationMockerNamespace* ns);

   VirtualTable* vtbl;
   ChainableMockMethodContainer* container;

   void reset();

private:
   ChainableMockMethodCore*
   createMethod(const std::string& name, void* addr, \
       unsigned int vptrIndex, unsigned int vtblIndex, \
       InvocationMockerNamespace* ns);
};

////////////////////////////////////////////////////////////////////////
MockObjectBaseImpl::
MockObjectBaseImpl(unsigned int numberOfVptr, ChainableMockMethodContainer* c)
    : vtbl(new VirtualTable(this, numberOfVptr)), container(c)
{
}
////////////////////////////////////////////////////////////////////////
MockObjectBaseImpl::~MockObjectBaseImpl()
{
   delete vtbl;
}

////////////////////////////////////////////////////////////////////////
void MockObjectBaseImpl::reset()
{
    vtbl->reset();
    container->reset();
}
////////////////////////////////////////////////////////////////////////
Invokable*
MockObjectBaseImpl::getInvokable(unsigned int vptrIndex, unsigned int vtblIndex) const
{
    ChainableMockMethodIndexKey key(vptrIndex, vtblIndex);

    return container->getMethod(&key);
}

////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
MockObjectBaseImpl::createMethod(const std::string& name, void* addr, \
       unsigned int vptrIndex, unsigned int vtblIndex, InvocationMockerNamespace* ns)
{
    ChainableMockMethodIndexKey* key = \
             new ChainableMockMethodIndexKey(vptrIndex, vtblIndex);
    ChainableMockMethodCore* method = new ChainableMockMethodCore(name, ns);
    
    container->addMethod(key, method);

    vtbl->addMethod(addr, vtblIndex, vptrIndex);
  
    return method;
}
////////////////////////////////////////////////////////////////////////
ChainableMockMethodCore*
MockObjectBaseImpl::getMethod(const std::string& name, void* addr, \
       unsigned int vptrIndex, unsigned int vtblIndex, \
       InvocationMockerNamespace* ns)
{
    ChainableMockMethodIndexKey key(vptrIndex, vtblIndex);
    ChainableMockMethodCore* method = container->getMethod(&key);
    if(method != 0)
    {
       return method;
    }

    return createMethod(name, addr, vptrIndex, vtblIndex, ns);
}

////////////////////////////////////////////////////////////////////////
MockObjectBase::MockObjectBase(const std::string& objName, unsigned int numberOfVptr)
   : ChainableMockObjectBase(objName), This(new MockObjectBaseImpl(numberOfVptr, this->getMethodContainer()))
{
}

////////////////////////////////////////////////////////////////////////
MockObjectBase::~MockObjectBase()
{
   delete This;
}

////////////////////////////////////////////////////////////////////////
InvocationMockBuilderGetter
MockObjectBase::createInvocationMockerBuilderGetter(const std::string& name, \
          void* addr, unsigned int vptrIndex, unsigned int vtblIndex)
{
   ChainableMockMethodCore* method = This->getMethod(name, addr, vptrIndex, vtblIndex, this);
   return InvocationMockBuilderGetter(method, method);
}

////////////////////////////////////////////////////////////////////////
void*
MockObjectBase::toPointerToInterface() const
{
   return This->vtbl->toPointerToInterface();
}

void
MockObjectBase::reset()
{
   This->reset();
}
////////////////////////////////////////////////////////////////////////


MOCKCPP_NS_END


#include <mockcpp.h>

#include <ChainableMockObjectBase.h>
#include <ChainableMockMethodCore.h>
#include <InvocationMocker.h>
#include <ChainableMockMethodContainer.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
class ChainableMockObjectBaseImpl
{
public:
    ChainableMockObjectBaseImpl(const std::string& name);

    ChainableMockMethodContainer container;
    std::string objectName;
};

//////////////////////////////////////////////////////////////
ChainableMockObjectBaseImpl::
ChainableMockObjectBaseImpl(const std::string& name)
   : objectName(name)
{
}

//////////////////////////////////////////////////////////////
ChainableMockObjectBase::
ChainableMockObjectBase(const std::string& name)
	: This(new ChainableMockObjectBaseImpl(name))
{
}

//////////////////////////////////////////////////////////////
ChainableMockObjectBase::~ChainableMockObjectBase()
{
	delete This;
}

//////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockObjectBase::
getInvocationMocker(const std::string& id) const
{
    return This->container.findInvocationMocker(id);
}

//////////////////////////////////////////////////////////////
void
ChainableMockObjectBase::verify()
{
    This->container.verify();
}

//////////////////////////////////////////////////////////////
std::string&
ChainableMockObjectBase::getName() const
{
    return This->objectName;
}

//////////////////////////////////////////////////////////////
ChainableMockMethodContainer*
ChainableMockObjectBase::getMethodContainer() const
{
   return &This->container;
}

//////////////////////////////////////////////////////////////

MOCKCPP_NS_END



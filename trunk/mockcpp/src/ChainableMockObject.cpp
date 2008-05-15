
#include <ChainableMockObject.h>
#include <Namespace.h>
#include <InvocationMockBuilder.h>
#include <InvocationMocker.h>

#include <list>
#include <algorithm>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
struct ChainableMockObjectImpl
{
    typedef std::list<ChainableMockMethodCore*> List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

    ChainableMockObjectImpl(const std::string& name);
	 ~ChainableMockObjectImpl();
    ChainableMockMethodCore* addMethodCore(const std::string& name, const Namespace* ns) const;
    ChainableMockMethodCore* findMethodCore(const std::string& name) const;
    InvocationMocker* findInvocationMocker(const std::string& id);
    void reset();
    void verify();

    mutable List methods;
    std::string objectName;

};

//////////////////////////////////////////////////////////////
namespace {
void verifyCore(ChainableMockMethodCore* core)
{
    core->verify();
}}

void ChainableMockObjectImpl::verify()
{
    for_each(methods.begin(), methods.end(), verifyCore);
}

//////////////////////////////////////////////////////////////
namespace {
void resetCore(ChainableMockMethodCore* core)
{
    core->reset();
    delete core;
}}

void ChainableMockObjectImpl::reset()
{
    for_each(methods.begin(), methods.end(), resetCore);
    methods.clear();
}

//////////////////////////////////////////////////////////////
ChainableMockObjectImpl::~ChainableMockObjectImpl()
{
    Iterator i = methods.begin();

    for (; i != methods.end(); ++i)
    {
      delete (*i);
    }

    methods.clear();
}

//////////////////////////////////////////////////////////////
struct IsMethodNameMatch
{
    IsMethodNameMatch(const std::string& methodName)
		: name(methodName)
    {}

    bool operator()(ChainableMockMethodCore* method)
    {
		return method->getName() == name;
    }

    const std::string& name;
};

//////////////////////////////////////////////////////////////
ChainableMockObjectImpl::ChainableMockObjectImpl(const std::string& name)
   : objectName(name)
{
}

//////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockObjectImpl::findInvocationMocker(const std::string& id)
{
	for (Iterator i = methods.begin(); i != methods.end(); ++i)
   {
		InvocationMocker* mocker = (*i)->getInvocationMocker(id);
      if(mocker != 0)
      {
         return mocker;
		}
	}

   return 0;
}
//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObjectImpl::addMethodCore( const std::string& name
                                      , const Namespace* ns) const
{
    ChainableMockMethodCore* core =
            new ChainableMockMethodCore(name, ns);

    methods.push_back(core);

    return core;
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObjectImpl::findMethodCore(const std::string& name) const
{
    ConstIterator i = std::find_if( methods.begin()
                             , methods.end()
                             , IsMethodNameMatch(name));

    return (i == methods.end()) ? 0 : (*i);
}

//////////////////////////////////////////////////////////////
ChainableMockObject::ChainableMockObject(
		const std::string& name
    , Namespace* ns )
	: This(new ChainableMockObjectImpl(name))
{
}

//////////////////////////////////////////////////////////////
ChainableMockObject::~ChainableMockObject()
{
	delete This;
}

//////////////////////////////////////////////////////////////
Method&
ChainableMockObject::method(const std::string& name)
{
    return *getMethod(name);
}

//////////////////////////////////////////////////////////////
ChainableMockMethodCore*
ChainableMockObject::getMethod(const std::string& name) const
{
    ChainableMockMethodCore* core = This->findMethodCore(name);
    if (core != 0)
    {
      return core;
    }

    return This->addMethodCore(name, this);
}

//////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockObject::getInvocationMocker(const std::string& id)
{
    return This->findInvocationMocker(id);
}

//////////////////////////////////////////////////////////////
void ChainableMockObject::reset()
{
    This->reset();
}

//////////////////////////////////////////////////////////////
void ChainableMockObject::verify()
{
    This->verify();
}

//////////////////////////////////////////////////////////////
std::string& ChainableMockObject::getName() const
{
    return This->objectName;
}
//////////////////////////////////////////////////////////////

MOCKCPP_NS_END



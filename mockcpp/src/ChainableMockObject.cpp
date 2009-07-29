
#include <mockcpp.h>

#include <ChainableMockObject.h>
#include <ChainableMockMethodCore.h>
#include <InvocationMockBuilder.h>
#include <InvocationMocker.h>
#include <ChainableMockMethodWithName.h>




#include <list>
#include <algorithm>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////
class ChainableMockObjectImpl
{
public:
    typedef std::list<ChainableMockMethodWithName*> List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

    ChainableMockObjectImpl(const std::string& name, InvocationMockerNamespace* ns);
	 ~ChainableMockObjectImpl();
    ChainableMockMethodWithName* addMethod(const std::string& name) const;
    ChainableMockMethodWithName* findMethod(const std::string& name) const;
    InvocationMocker* findInvocationMocker(const std::string& id);
    void reset();
    void verify();

    mutable List methods;
    std::string objectName;
    InvocationMockerNamespace* invocationMockerNamespace;

};

//////////////////////////////////////////////////////////////
namespace {
void verifyCore(ChainableMockMethodWithName* method)
{
    method->verify();
}}

void ChainableMockObjectImpl::verify()
{
    for_each(methods.begin(), methods.end(), verifyCore);
}

//////////////////////////////////////////////////////////////
namespace {
void resetCore(ChainableMockMethodWithName* method)
{
    method->reset();
    delete method;
}}

void ChainableMockObjectImpl::reset()
{
    for_each(methods.begin(), methods.end(), resetCore);
    methods.clear();
}

//////////////////////////////////////////////////////////////
ChainableMockObjectImpl::~ChainableMockObjectImpl()
{
    reset();
}

//////////////////////////////////////////////////////////////
struct IsMethodNameMatch
{
    IsMethodNameMatch(const std::string& methodName)
		: name(methodName)
    {}

    bool operator()(ChainableMockMethodWithName* method)
    {
		return method->getMethodName() == name;
    }

    const std::string& name;
};

//////////////////////////////////////////////////////////////
ChainableMockObjectImpl::ChainableMockObjectImpl(const std::string& name, \
			InvocationMockerNamespace* ns)
   : objectName(name), invocationMockerNamespace(ns)
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
ChainableMockMethodWithName*
ChainableMockObjectImpl::addMethod(const std::string& name) const
{
    ChainableMockMethodWithName* method =
            new ChainableMockMethodWithName(name, invocationMockerNamespace);

    methods.push_back(method);

    return method;
}

//////////////////////////////////////////////////////////////
ChainableMockMethodWithName*
ChainableMockObjectImpl::findMethod(const std::string& name) const
{
    ConstIterator i = std::find_if( methods.begin()
                             , methods.end()
                             , IsMethodNameMatch(name));

    return (i == methods.end()) ? 0 : (*i);
}

//////////////////////////////////////////////////////////////
ChainableMockObject::ChainableMockObject(
		const std::string& name)
	: This(new ChainableMockObjectImpl(name, this))
{
}

//////////////////////////////////////////////////////////////
ChainableMockObject::~ChainableMockObject()
{
	delete This;
}

//////////////////////////////////////////////////////////////
InvocationMockBuilderGetter&
ChainableMockObject::method(const std::string& name)
{
    return *(getMethod(name)->getInvocationMockBuilderGetter());
}

Invokable*
ChainableMockObject::getInvokable(const std::string& name) const
{
   return getMethod(name)->getInvokable();
}
//////////////////////////////////////////////////////////////
ChainableMockMethodWithName*
ChainableMockObject::getMethod(const std::string& name) const
{
    ChainableMockMethodWithName* method = This->findMethod(name);
    if (method != 0)
    {
      return method;
    }

    return This->addMethod(name);
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



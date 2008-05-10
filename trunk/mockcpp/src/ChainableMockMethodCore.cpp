
#include <ChainableMockMethodCore.h>
#include <InvocationMocker.h>
#include <Any.h>
#include <Stub.h>
#include <Asserter.h>
#include <Invocation.h>
#include <InvocationId.h>

#include <list>
#include <algorithm>

#include <iostream>

using namespace std;

MOCKCPP_NS_START

//////////////////////////////////////////////////////////
struct ChainableMockMethodCoreImpl
{
    typedef std::list<InvocationMocker*> List;
    typedef List::iterator Iterator;
    typedef List::const_iterator ConstIterator;

    /////////////////////////////////////////////////////
    List mockers;
    std::string name;
    Namespace* nameSpace;
    Stub* defaultStub;

	 /////////////////////////////////////////////////////
    ChainableMockMethodCoreImpl(const std::string& s, Namespace* ns)
      : name(s), nameSpace(ns), defaultStub(0)
    {}
 
    ~ChainableMockMethodCoreImpl();
   
    InvocationMocker* getInvocationMocker(const std::string& id) const;
    std::string tellNoMatchedExpectation(const Invocation& inv);
    std::string toString(bool wide) const;
    Any& invoke(const Invocation& inv);
    void reset();
    void verify();
};

/////////////////////////////////////////////////////////////
std::string ChainableMockMethodCoreImpl::toString(bool wide) const
{
	std::ostringstream ss;
	ConstIterator i = mockers.begin();
	cout << "number of mockers:" << mockers.size() << endl;
   for(; i != mockers.end(); i++) {
      ss << (*i)->toString(wide) << "\n"; 
   }

   return ss.str();
}
/////////////////////////////////////////////////////////////
namespace {
void verifyMocker(InvocationMocker* mocker)
{
    mocker->verify();
}}

void ChainableMockMethodCoreImpl::verify()
{
    for_each(mockers.begin(), mockers.end(), verifyMocker);
}
/////////////////////////////////////////////////////////////
ChainableMockMethodCoreImpl::~ChainableMockMethodCoreImpl()
{
	reset();
}

/////////////////////////////////////////////////////////////
namespace {
void deleteMocker(InvocationMocker* mocker)
{
    delete mocker;
}}

void ChainableMockMethodCoreImpl::reset()
{
    for_each(mockers.begin(), mockers.end(), deleteMocker);

    mockers.clear();

    if(defaultStub != 0) {
       delete defaultStub;
       defaultStub = 0;
    }
}
   
namespace {
struct IsIdEqual
{
   bool operator()(InvocationMocker* mocker) const
   {
      const InvocationId* const invId = mocker->getId();
      return invId && invId->getId() == id;
   }

	IsIdEqual(const std::string& identity)
		: id(identity)
	{}

	const std::string& id;
};
}

/////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCoreImpl::
getInvocationMocker(const std::string& id) const
{
   ConstIterator i = find_if( mockers.begin()
									 , mockers.end()
									 , IsIdEqual(id));
   if(i == mockers.end())
      return 0;

   return (*i);
}
/////////////////////////////////////////////////////////////
std::string
ChainableMockMethodCoreImpl::
tellNoMatchedExpectation(const Invocation& inv)
{
    return std::string("Unexpected invocation") + "\n" 
                     + "Invoked: " + name + inv.toString() + "\n" 
                     + "Allowed: " + this->toString(true);
}
/////////////////////////////////////////////////////////////
Any&
ChainableMockMethodCoreImpl::invoke(const Invocation& inv)
{
	for(Iterator i = mockers.begin(); i != mockers.end(); ++i) {
	  if((*i)->matches(inv)) {
		 return (*i)->invoke(inv);
	  }
	}

	if(defaultStub != 0) {
	  return defaultStub->invoke(inv);
	}


	MOCKCPP_FAIL(tellNoMatchedExpectation(inv));
   
	return const_cast<Any&>(EmptyAny);
}
//////////////////////////////////////////////////////////
ChainableMockMethodCore::
ChainableMockMethodCore(const std::string& name, Namespace* ns)
   : This(new ChainableMockMethodCoreImpl(name, ns))
{
}

//////////////////////////////////////////////////////////
ChainableMockMethodCore::~ChainableMockMethodCore()
{
    delete This;
}

//////////////////////////////////////////////////////////
std::string&
ChainableMockMethodCore::getName(void) const
{
    return This->name;
}

//////////////////////////////////////////////////////////
Namespace*
ChainableMockMethodCore::getNamespace() const
{
    return This->nameSpace;
}

//////////////////////////////////////////////////////////
Any&
ChainableMockMethodCore::invoke(const Invocation& invocation)
{
	return This->invoke(invocation);
}

//////////////////////////////////////////////////////////
void
ChainableMockMethodCore::setDefaultStub(Stub* stub)
{
	This->defaultStub = stub;
}

//////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCore::getInvocationMocker(const std::string& id)
{
   return This->getInvocationMocker(id);
}

//////////////////////////////////////////////////////////
void
ChainableMockMethodCore::addInvocationMocker(InvocationMocker* mocker)
{
   This->mockers.push_back(mocker);
}

//////////////////////////////////////////////////////////
InvocationMockBuilder ChainableMockMethodCore::stubs()
{
    InvocationMocker* mocker = new InvocationMocker(this);
    addInvocationMocker(mocker);
    return InvocationMockBuilder(mocker);
}

//////////////////////////////////////////////////////////
InvocationMockBuilder ChainableMockMethodCore::expects(Matcher* matcher)
{
    InvocationMocker* mocker = new InvocationMocker(this);
	 mocker->addMatcher(matcher);
    addInvocationMocker(mocker);
    return InvocationMockBuilder(mocker);
}

//////////////////////////////////////////////////////////
void ChainableMockMethodCore::reset()
{
    This->reset();
}

//////////////////////////////////////////////////////////
void ChainableMockMethodCore::verify()
{
    This->verify();
}
//////////////////////////////////////////////////////////

MOCKCPP_NS_END


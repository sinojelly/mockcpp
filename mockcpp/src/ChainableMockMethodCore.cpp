
#include <ChainableMockMethodCore.h>
#include <InvocationMockerSet.h>
#include <InvocationMocker.h>
#include <Any.h>
#include <Stub.h>
#include <Asserter.h>
#include <Invocation.h>
#include <InvocationId.h>
#include <DefaultMatcher.h>
#include <StubsMatcher.h>
#include <ExpectsMatcher.h>
#include <InvokedTimesMatcher.h>
#include <SimpleInvocationRecorder.h>
#include <InvokedTimesRecorder.h>
#include <InvocationTimesMatcher.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////
struct ChainableMockMethodCoreImpl
{
    /////////////////////////////////////////////////////
    InvocationMockerSet mockers;
    InvocationMockerSet defaultMockers;
    std::string name;
    Namespace* nameSpace;

	 /////////////////////////////////////////////////////
    ChainableMockMethodCoreImpl(const std::string& s, Namespace* ns)
      : name(s), nameSpace(ns)
    {}
 
    ~ChainableMockMethodCoreImpl();
   
    InvocationMocker* getInvocationMocker(const std::string& id) const;
    std::string tellNoMatchedExpectation(const Invocation& inv);
    std::string toString() const;
    Any invoke(const Invocation& inv, SelfDescribe* &resultProvider);
    void reset();
    void verify();
};

/////////////////////////////////////////////////////////////
std::string ChainableMockMethodCoreImpl::toString() const
{
    return mockers.toString() + defaultMockers.toString();
}

/////////////////////////////////////////////////////////////
void ChainableMockMethodCoreImpl::verify()
{
    mockers.verify();
}

/////////////////////////////////////////////////////////////
ChainableMockMethodCoreImpl::~ChainableMockMethodCoreImpl()
{
    reset();
}

/////////////////////////////////////////////////////////////
void ChainableMockMethodCoreImpl::reset()
{
    mockers.reset();
    defaultMockers.reset();
}
 
/////////////////////////////////////////////////////////////
InvocationMocker*
ChainableMockMethodCoreImpl::
getInvocationMocker(const std::string& id) const
{
    return mockers.getInvocationMocker(id);
}

/////////////////////////////////////////////////////////////
std::string
ChainableMockMethodCoreImpl::
tellNoMatchedExpectation(const Invocation& inv)
{
    return std::string("Unexpected invocation") + "\n" 
                     + "Invoked: " + nameSpace->getName() + "::" + name + inv.toString() + "\n" 
                     + "Allowed: \n"
                     + this->toString();
}

/////////////////////////////////////////////////////////////
Any
ChainableMockMethodCoreImpl::invoke(const Invocation& inv
                                   , SelfDescribe* &resultProvider)
{
	Any result = mockers.invoke(inv, resultProvider);
	if(!result.empty()) {
      return result;
   }

	result = defaultMockers.invoke(inv, resultProvider);
	if(!result.empty()) {
      return result;
   }

	MOCKCPP_FAIL(tellNoMatchedExpectation(inv));
   
	return getEmptyAny();
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
Any
ChainableMockMethodCore::invoke(const Invocation& invocation
		, SelfDescribe* &resultProvider)
{
	return This->invoke(invocation, resultProvider);
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
   This->mockers.addInvocationMocker(mocker);
}

//////////////////////////////////////////////////////////
WorkingBuilder ChainableMockMethodCore::stubs()
{
    InvocationMocker* mocker = new InvocationMocker(this);
	 mocker->addMatcher(new StubsMatcher);
    mocker->addMatcher(new InvokedTimesMatcher(new SimpleInvocationRecorder));
    addInvocationMocker(mocker);
    return WorkingBuilder(mocker);
}

//////////////////////////////////////////////////////////
WorkingBuilder ChainableMockMethodCore::expects(Matcher* matcher)
{
    InvocationMocker* mocker = new InvocationMocker(this);

    InvokedTimesRecorder* recorder = new SimpleInvocationRecorder;
    InvocationTimesMatcher* itMatcher = dynamic_cast<InvocationTimesMatcher*>(matcher);
    if (itMatcher != 0)
    {
      itMatcher->setInvokedTimesReader(recorder);
    }

    mocker->addMatcher(new ExpectsMatcher(matcher));
    mocker->addMatcher(new InvokedTimesMatcher(recorder));

    addInvocationMocker(mocker);

    return WorkingBuilder(mocker);
}

//////////////////////////////////////////////////////////
DefaultBuilder ChainableMockMethodCore::defaults()
{
    InvocationMocker* mocker = new InvocationMocker(this);
	 mocker->addMatcher(new DefaultMatcher);
    This->defaultMockers.addInvocationMocker(mocker);
    return DefaultBuilder(mocker);
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


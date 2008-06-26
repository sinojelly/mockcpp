
#include <Any.h>
#include <Stub.h>
#include <Asserter.h>
#include <Invocation.h>
#include <InvocationId.h>
#include <DefaultMatcher.h>
#include <StubsMatcher.h>
#include <ExpectsMatcher.h>
#include <InvocationMocker.h>
#include <InvokedTimesMatcher.h>
#include <InvocationMockerSet.h>
#include <InvokedTimesRecorder.h>
#include <InvocationTimesMatcher.h>
#include <ChainableMockMethodCore.h>
#include <SimpleInvocationRecorder.h>

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
    ChainableMockMethodCoreImpl(const std::string& s, const Namespace* ns)
      : name(s), nameSpace(const_cast<Namespace*>(ns))
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
	if (!result.empty())
    {
      return result;
    }

    result = defaultMockers.invoke(inv, resultProvider);
    if (!result.empty())
    {
      return result;
    }

	MOCKCPP_FAIL(tellNoMatchedExpectation(inv));
   
	return getEmptyAny();
}

//////////////////////////////////////////////////////////
ChainableMockMethodCore::
ChainableMockMethodCore(const std::string& name, const Namespace* ns)
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
ChainableMockMethodCore::invoke
             ( const RefAny& p1
             , const RefAny& p2
             , const RefAny& p3
             , const RefAny& p4
             , const RefAny& p5
             , const RefAny& p6
             , const RefAny& p7
             , const RefAny& p8
             , const RefAny& p9
             , const RefAny& p10
             , const RefAny& p11
             , const RefAny& p12
             , SelfDescribe* &resultProvider)
{
	Invocation inv(p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12);
	return This->invoke(inv, resultProvider);
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


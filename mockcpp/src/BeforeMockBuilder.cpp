
#include <BeforeMatchBuilder.h>
#include <Namespace.h>
#include <InvocationMocker.h>
#include <ChainableMockMethodCore.h>
#include <Matcher.h>

MOCKCPP_NS_START

struct BeforeMatcher : public Matcher
{
   BeforeMatcher(InvocationMocker* mocker)
		: invocationMocker(mocker)
	{}

	bool matches(const Invocation& inv) const
   {
     return !invocationMocker->isInvoked();
   }

   void increaseInvoked(const Invocation& inv)
   {
   // if(!matches(inv))
   //     throw exception;
   }

	std::string toString() const
	{
		return std::string("");
	}

   InvocationMocker* invocationMocker;
};

//////////////////////////////////////////////////////////////////////
ArgumentsMatchBuilder&
BeforeMatchBuilder::before(const Namespace& ns, const std::string& name)
{
    return before(&const_cast<Namespace&>(ns), name);
}

//////////////////////////////////////////////////////////////////////
ArgumentsMatchBuilder&
BeforeMatchBuilder::before(Namespace* ns, const std::string& name)
{
    InvocationMocker* mocker = ns->getInvocationMocker(name);
    if(mocker != 0) {
      setupOrderingBeforeMatchers(mocker);
    }

    return *this;
}

//////////////////////////////////////////////////////////////////////
ArgumentsMatchBuilder&
BeforeMatchBuilder::before(const std::string& name)
{
    return before(getMocker()->getMethod()->getNamespace(), name);
}

//////////////////////////////////////////////////////////////////////
void
BeforeMatchBuilder::setupOrderingBeforeMatchers(InvocationMocker* mocker)
{
    getMocker()->addMatcher(new BeforeMatcher(mocker));
}

MOCKCPP_NS_END




#include <AfterMatchBuilder.h>
#include <Namespace.h>
#include <InvocationMocker.h>
#include <ChainableMockMethodCore.h>
#include <Matcher.h>

MOCKCPP_NS_START

struct AfterMatcher : public Matcher
{
	AfterMatcher(InvocationMocker* m)
		: mocker(m)
   {
	}

   bool matches(const Invocation& inv) const
   {
      return mocker->isInvoked();
   }

   void increaseInvoked(const Invocation& inv)
   {
   // if(!matches(inv))
   //    throw exception;
   }

	std::string toString() const
	{
		return std::string("");
	}

	InvocationMocker* mocker;
};

/////////////////////////////////////////////////////////////
StubBuilder&
AfterMatchBuilder::after(const Namespace& ns, const std::string& name)
{
    return after(&const_cast<Namespace&>(ns), name);
}

/////////////////////////////////////////////////////////////
StubBuilder&
AfterMatchBuilder::after(Namespace* ns, const std::string& name)
{
    InvocationMocker* mocker = ns->getInvocationMocker(name);
    if(mocker != 0) {
      setupOrderingAfterMatchers(mocker);
    }

    return *this;
}

/////////////////////////////////////////////////////////////
StubBuilder&
AfterMatchBuilder::after(const std::string& name)
{
    return after(getMocker()->getMethod()->getNamespace(), name);
}

/////////////////////////////////////////////////////////////
void
AfterMatchBuilder::setupOrderingAfterMatchers(InvocationMocker* mocker)
{
    getMocker()->addMatcher(new AfterMatcher(mocker));
}
    
/////////////////////////////////////////////////////////////

MOCKCPP_NS_END



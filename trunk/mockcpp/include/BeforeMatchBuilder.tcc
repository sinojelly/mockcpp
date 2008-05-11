
#include <Namespace.h>
#include <InvocationMocker.h>
#include <ChainableMockMethodCore.h>
#include <BeforeMatcher.h>
#include <PendingMatcher.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
BeforeMatchBuilder<Builder>::before(const Namespace& ns, const std::string& name)
{
    return before(&const_cast<Namespace&>(ns), name);
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
BeforeMatchBuilder<Builder>::before(Namespace* ns, const std::string& id)
{
    getMocker()->addMatcher(
			new PendingMatcher(
				new BeforeMatcher(ns->getInvocationMocker(id))
				, ns , id , getMocker()));

    return *this;
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
BeforeMatchBuilder<Builder>::before(const std::string& name)
{
    return before(getMocker()->getMethod()->getNamespace(), name);
}

//////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END



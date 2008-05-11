
#include <Namespace.h>
#include <InvocationMocker.h>
#include <ChainableMockMethodCore.h>
#include <AfterMatcher.h>
#include <PendingMatcher.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
AfterMatchBuilder<Builder>::after(const Namespace& ns, const std::string& name)
{
    return after(&const_cast<Namespace&>(ns), name);
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
AfterMatchBuilder<Builder>::after(Namespace* ns, const std::string& id)
{
    getMocker()->addMatcher(
			new PendingMatcher(
				new AfterMatcher(ns->getInvocationMocker(id))
				, ns, id, getMocker())); 
    return *this;
}

//////////////////////////////////////////////////////////////////////
template <class Builder>
Builder&
AfterMatchBuilder<Builder>::after(const std::string& name)
{
    return after(getMocker()->getMethod()->getNamespace(), name);
}

//////////////////////////////////////////////////////////////////////

MOCKCPP_NS_END



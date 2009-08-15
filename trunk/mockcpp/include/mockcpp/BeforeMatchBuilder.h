
#ifndef __MOCKCPP_BEFORE_MATCH_BUILDER_H
#define __MOCKCPP_BEFORE_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

class InvocationMockerNamespace;
class InvocationMocker;

template <class Builder = DummyBuilder >
class BeforeMatchBuilder : public Builder
{
public:
    
    BeforeMatchBuilder&
	 before(const InvocationMockerNamespace& ns, const std::string& name);

    BeforeMatchBuilder&
	 before(InvocationMockerNamespace* ns, const std::string& name);

    BeforeMatchBuilder&
	 before(const std::string& name);

private:

    void
    setupOrderingBeforeMatchers(InvocationMocker* mocker);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <mockcpp/BeforeMatchBuilder.tcc>

#endif


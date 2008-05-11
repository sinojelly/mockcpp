
#ifndef __MOCKCPP_BEFORE_MATCH_BUILDER_H
#define __MOCKCPP_BEFORE_MATCH_BUILDER_H

#include <mockcpp.h>
#include <DummyBuilder.h>

MOCKCPP_NS_START

class Namespace;
class InvocationMocker;

template <class Builder = DummyBuilder >
class BeforeMatchBuilder : public Builder
{
public:
    
    Builder&
	 before(const Namespace& ns, const std::string& name);

    Builder&
	 before(Namespace* ns, const std::string& name);

    Builder&
	 before(const std::string& name);

private:

    void
    setupOrderingBeforeMatchers(InvocationMocker* mocker);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <BeforeMatchBuilder.tcc>

#endif


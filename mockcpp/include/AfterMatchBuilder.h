
#ifndef __MOCKCPP_AFTER_MATCH_BUILDER_H
#define __MOCKCPP_AFTER_MATCH_BUILDER_H

#include <mockcpp.h>

#include <DummyBuilder.h>

MOCKCPP_NS_START

class InvocationMockerNamespace;
class InvocationMocker;

template <class Builder = DummyBuilder>
class AfterMatchBuilder : public Builder
{
public:
    
    Builder&
    after(const InvocationMockerNamespace& ns, const std::string& name);

    Builder&
    after(InvocationMockerNamespace* ns, const std::string& name);

    Builder&
    after(const std::string& name);

private:
    void
    setupOrderingAfterMatchers(InvocationMocker* mocker);
    
private:
    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <AfterMatchBuilder.tcc>

#endif



#ifndef __MOCKCPP_AFTER_MATCH_BUILDER_H
#define __MOCKCPP_AFTER_MATCH_BUILDER_H

#include <mockcpp.h>

#include <StubBuilder.h>

MOCKCPP_NS_START

class Namespace;
class InvocationMocker;

class AfterMatchBuilder : public StubBuilder
{
public:
    
    StubBuilder&
    after(const Namespace& ns, const std::string& name);

    StubBuilder&
    after(Namespace* ns, const std::string& name);

    StubBuilder&
    after(const std::string& name);

private:
    void
    setupOrderingAfterMatchers(InvocationMocker* mocker);
    
private:
    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#endif


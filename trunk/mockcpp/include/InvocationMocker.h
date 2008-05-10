
#ifndef __MOCKCPP_INVOCATION_MOCKER_H
#define __MOCKCPP_INVOCATION_MOCKER_H

#include <mockcpp.h>

#include <string>

MOCKCPP_NS_START

class ChainableMockMethodCore;
class Matcher;
class Stub;
class InvocationMockerImpl;
class Invocation;
class InvocationId;
class Any;

class InvocationMocker
{
public:

    InvocationMocker(ChainableMockMethodCore* core);
    ~InvocationMocker();

    ChainableMockMethodCore* getMethod() const;
    void setStub(Stub* stub);
    void addMatcher(Matcher* matcher);
    bool isInvoked(void) const ;

    void setId(InvocationId* id);
    const InvocationId* const getId(void) const;

    bool matches(const Invocation& inv) const;
    Any& invoke(const Invocation& inv);

    void verify();
    std::string toString(bool wide) const;

private:
    InvocationMockerImpl* This;
};

MOCKCPP_NS_END

#endif


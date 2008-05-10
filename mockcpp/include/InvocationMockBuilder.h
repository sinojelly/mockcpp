
#ifndef __MOCKCPP_INVOCATION_MOCK_BUILDER_H
#define __MOCKCPP_INVOCATION_MOCK_BUILDER_H

#include <mockcpp.h>
#include <BeforeMatchBuilder.h>

MOCKCPP_NS_START

class Matcher;
class InvocationMocker;

class InvocationMockBuilder : public BeforeMatchBuilder
{
public:
    InvocationMockBuilder(InvocationMocker* mocker);

private:
    virtual InvocationMocker* getMocker() const;

private:
    InvocationMocker* invocationMocker;
};

MOCKCPP_NS_END

#endif


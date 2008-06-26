
#ifndef __MOCKCPP_INVOCATION_MOCK_BUILDER_H
#define __MOCKCPP_INVOCATION_MOCK_BUILDER_H

#include <mockcpp.h>
#include <DummyBuilder.h>

MOCKCPP_NS_START

class Matcher;
class InvocationMocker;

template <typename Builder = DummyBuilder>
class InvocationMockBuilder : public Builder
{
public:

   InvocationMockBuilder(InvocationMocker* mocker);

private:

   virtual InvocationMocker* getMocker() const;

private:

   InvocationMocker* invocationMocker;
};

MOCKCPP_NS_END

#include <InvocationMockBuilder.tcc>

#endif


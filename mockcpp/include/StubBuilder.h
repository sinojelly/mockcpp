
#ifndef __MOCKCPP_STUB_BUILDER_H
#define __MOCKCPP_STUB_BUILDER_H

#include <mockcpp.h>
#include <DummyBuilder.h>

MOCKCPP_NS_START

class InvocationMocker;
class Stub;

template <class Builder = DummyBuilder >
class StubBuilder : public Builder
{
public:

    Builder& will(Stub* stub);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <StubBuilder.tcc>

#endif


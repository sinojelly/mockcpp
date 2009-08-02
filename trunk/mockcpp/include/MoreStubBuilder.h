
#ifndef __MOCKCPP_MORE_STUB_BUILDER_H
#define __MOCKCPP_MORE_STUB_BUILDER_H

#include <mockcpp.h>
#include <DummyBuilder.h>

MOCKCPP_NS_START

class InvocationMocker;
class Stub;

template <class Builder = DummyBuilder >
class MoreStubBuilder : public Builder
{
public:

    Builder& then(Stub* stub);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#include <MoreStubBuilder.tcc>

#endif



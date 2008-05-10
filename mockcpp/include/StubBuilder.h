
#ifndef __MOCKCPP_STUB_BUILDER_H
#define __MOCKCPP_STUB_BUILDER_H

#include <mockcpp.h>
#include <IdentityBuilder.h>

MOCKCPP_NS_START

class Stub;

class StubBuilder : public IdentityBuilder
{
public:

    IdentityBuilder& will(Stub* stub);

private:

    virtual InvocationMocker* getMocker() const = 0;
};

MOCKCPP_NS_END

#endif



#include <StubBuilder.h>
#include <ChainableMockMethodCore.h>
#include <InvocationMocker.h>
#include <Stub.h>

MOCKCPP_NS_START

IdentityBuilder& StubBuilder::will(Stub* stub)
{
    getMocker()->setStub(stub);
    return *this;
}

MOCKCPP_NS_END




#include <InvocationMocker.h>
#include <WillStub.h>

MOCKCPP_NS_START

template<class Builder>
Builder& StubBuilder<Builder>::will(Stub* stub)
{
    getMocker()->setStub(new WillStub(stub));
    return *this;
}

MOCKCPP_NS_END



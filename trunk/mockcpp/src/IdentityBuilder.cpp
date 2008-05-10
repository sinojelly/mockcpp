
#include <IdentityBuilder.h>
#include <InvocationMocker.h>
#include <InvocationId.h>

MOCKCPP_NS_START

void IdentityBuilder::id(const std::string& id)
{
	getMocker()->setId(new InvocationId(id));
}


MOCKCPP_NS_END



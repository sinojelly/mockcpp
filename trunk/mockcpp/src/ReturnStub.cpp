
#include <ReturnStub.h>

MOCKCPP_NS_START

ReturnStub::ReturnStub(const Any& value)
		: returnValue(value)
{}

Any& ReturnStub::invoke(void)
{
    return returnValue;
}

std::string ReturnStub::toString(void) const
{
    return std::string(".will(returnValue(") +
           returnValue.toTypeAndValueString() + 
           std::string("))");
}

MOCKCPP_NS_END


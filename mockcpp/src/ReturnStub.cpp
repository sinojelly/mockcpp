
#include <ReturnStub.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
ReturnStub::ReturnStub(const Any& value)
		: returnValue(value)
{}

/////////////////////////////////////////////////////
Any& ReturnStub::invoke(void)
{
    return returnValue;
}

/////////////////////////////////////////////////////
const std::type_info& ReturnStub::type() const
{
    return returnValue.type();
}

/////////////////////////////////////////////////////
std::string ReturnStub::toString(void) const
{
    return std::string("returnValue(") +
           returnValue.toTypeAndValueString() + 
           std::string(")");
}

MOCKCPP_NS_END


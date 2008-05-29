
#include <IgnoreReturnStub.h>
#include <Ignore.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////
Any&
IgnoreReturnStub::invoke()
{
    return getIgnore();
}

/////////////////////////////////////////////////////
std::string IgnoreReturnStub::toString(void) const
{
    return "ignoreReturnValue()";
}

/////////////////////////////////////////////////////
const std::type_info& IgnoreReturnStub::type() const
{
    return typeid(Ignore);
}

/////////////////////////////////////////////////////

MOCKCPP_NS_END


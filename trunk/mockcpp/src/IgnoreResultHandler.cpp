
#include <IgnoreResultHandler.h>
#include <Any.h>
#include <Ignore.h>

MOCKCPP_NS_START

bool IgnoreResultHandler::matches(const Any& val) const
{
   return any_castable<Ignore>(val);
}

Any& IgnoreResultHandler::getResult(const Any& val) const
{
	return getEmptyAny();
}

MOCKCPP_NS_END


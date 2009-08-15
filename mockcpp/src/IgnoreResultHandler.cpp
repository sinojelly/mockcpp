
#include <mockcpp/IgnoreResultHandler.h>
#include <mockcpp/Any.h>
#include <mockcpp/Ignore.h>

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


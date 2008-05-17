
#include <IgnoreResultHandlerFactory.h>
#include <IgnoreResultHandler.h>
#include <SelfDescribe.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ResultHandler* IgnoreResultHandlerFactory::create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
{
    return new IgnoreResultHandler();
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END


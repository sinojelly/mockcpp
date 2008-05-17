
#include <VoidResultHandlerFactory.h>
#include <VoidResultHandler.h>
#include <SelfDescribe.h>
#include <string>

MOCKCPP_NS_START

ResultHandler* VoidResultHandlerFactory::create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
{
    return new VoidResultHandler(expectedTypeInfo, expectedTypeString, selfDescriber);
}


MOCKCPP_NS_END


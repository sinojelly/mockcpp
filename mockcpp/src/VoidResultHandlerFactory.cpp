
#include <mockcpp/VoidResultHandlerFactory.h>
#include <mockcpp/VoidResultHandler.h>
#include <mockcpp/SelfDescribe.h>
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


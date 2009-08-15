
#include <mockcpp/NormalResultHandlerFactory.h>
#include <mockcpp/NormalResultHandler.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ResultHandler* NormalResultHandlerFactory::create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber)
{
    return new NormalResultHandler(expectedTypeInfo);
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END


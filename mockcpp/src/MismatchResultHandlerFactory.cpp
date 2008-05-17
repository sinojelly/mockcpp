
#include <MismatchResultHandlerFactory.h>
#include <MismatchResultHandler.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
ResultHandler* MismatchResultHandlerFactory::create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* resultProvider)
{
    return new MismatchResultHandler(expectedTypeInfo
                         , expectedTypeString
                         , resultProvider);
}

///////////////////////////////////////////////////////////

MOCKCPP_NS_END


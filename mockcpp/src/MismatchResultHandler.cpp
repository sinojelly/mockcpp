
#include <MismatchResultHandler.h>
#include <Any.h>
#include <SelfDescribe.h>
#include <Asserter.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
MismatchResultHandler::MismatchResultHandler(
                           const std::type_info& info
                         , const std::string& typeString
                         , const SelfDescribe* selfDescriber)
			  : expectedTypeInfo(info)
			  , expectedTypeString(typeString)
			  , resultProvider(selfDescriber)
{
}

////////////////////////////////////////////////////////////////
bool MismatchResultHandler::matches(const Any& result) const
{
      return result.type() != expectedTypeInfo;
}

////////////////////////////////////////////////////////////////
Any& MismatchResultHandler::getResult(const Any& result) const
{
    oss_t oss;

    oss << "Returned type does NOT match the method declaration \n"
        << "Required : " << expectedTypeString << "\n"
        << "Returned : " << result.toTypeString() << ", which is from\n"
        << resultProvider->toString();

    MOCKCPP_ASSERT_FALSE_MESSAGE(oss.str(), matches(result));

    return getEmptyAny();
}

MOCKCPP_NS_END


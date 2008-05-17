
#ifndef __MOCKCPP_MISMATCH_RESULT_HANDLER_H
#define __MOCKCPP_MISMATCH_RESULT_HANDLER_H

#include <mockcpp.h>
#include <ResultHandler.h>

MOCKCPP_NS_START

class Any;
class SelfDescribe;

struct MismatchResultHandler: public ResultHandler
{
public:

    MismatchResultHandler( const std::type_info& expectedTypeInfo
                         , const std::string& expectedTypeString
                         , const SelfDescribe* resultProvider);

    bool matches(const Any& result) const;

    Any& getResult(const Any& result) const;

private:
    const std::type_info& expectedTypeInfo;
    const std::string& expectedTypeString;
    const SelfDescribe* resultProvider;
};

MOCKCPP_NS_END

#endif


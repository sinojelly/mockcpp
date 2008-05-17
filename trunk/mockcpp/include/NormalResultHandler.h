
#ifndef __MOCKCPP_NORMAL_RESULT_HANDLER_H
#define __MOCKCPP_NORMAL_RESULT_HANDLER_H

#include <mockcpp.h>
#include <ResultHandler.h>

MOCKCPP_NS_START

class Any;

class NormalResultHandler : public ResultHandler
{
public:

    NormalResultHandler(const std::type_info& type);

    bool matches(const Any& result) const;

    Any& getResult(const Any& result) const;

private:

    const std::type_info& expectedTypeInfo;

};

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_IGNORE_RESULT_HANDLER_H
#define __MOCKCPP_IGNORE_RESULT_HANDLER_H

#include <mockcpp.h>
#include <ResultHandler.h>

MOCKCPP_NS_START

class Any;

class IgnoreResultHandler : public ResultHandler
{
public:

    bool matches(const Any& result) const;

    Any& getResult(const Any& result) const;
};

MOCKCPP_NS_END

#endif


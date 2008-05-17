
#ifndef __MOCKCPP_RESULT_HANDLER_H
#define __MOCKCPP_RESULT_HANDLER_H

#include <mockcpp.h>
#include <string>

MOCKCPP_NS_START

class Any;

struct ResultHandler
{
    virtual ~ResultHandler() {}

    virtual bool matches(const Any& val) const = 0;
    virtual Any& getResult(const Any& val) const = 0;
};

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_RESULT_HANDLER_H
#define __MOCKCPP_RESULT_HANDLER_H

#include <mockcpp.h>
#include <ResultHandler.h>
#include <Ignore.h>

MOCKCPP_NS_START

class Any;

struct IgnoreHandler : public ResultHandler
{
    bool matches(const Any& val) const
    {
      return any_castable<Ignore>(val);
    }

    Any& getResult() const
    {
      return getEmtpyHandler();
    }
};

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_TYPELESS_MATCHER_H
#define __MOCKCPP_TYPELESS_MATCHER_H

#include <mockcpp.h>
#include <string>

MOCKCPP_NS_START

struct TypelessMatcher
{
    virtual ~TypelessMatcher() {}
    virtual bool matches(void) const = 0;
    virtual void increaseInvoked(void) = 0;
    virtual std::string toString() const = 0;
    virtual void verify() {}
};

MOCKCPP_NS_END

#endif


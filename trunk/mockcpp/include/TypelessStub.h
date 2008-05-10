
#ifndef __MOCKCPP_TYPELESS_STUB_H
#define __MOCKCPP_TYPELESS_STUB_H

#include <mockcpp.h>
#include <string>

MOCKCPP_NS_START

class Any;

struct TypelessStub
{
    virtual Any& invoke(void) = 0;
    virtual std::string toString(void) const = 0;
};

MOCKCPP_NS_END

#endif


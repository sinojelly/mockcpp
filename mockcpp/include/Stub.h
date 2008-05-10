
#ifndef __MOCKCPP_STUB_H
#define __MOCKCPP_STUB_H

#include <mockcpp.h>
#include <string>

MOCKCPP_NS_START

class Any;
class Invocation;

struct Stub
{
    virtual ~Stub() {}
    virtual Any& invoke(const Invocation& inv) = 0;
    virtual std::string toString() const = 0;
};

MOCKCPP_NS_END

#endif


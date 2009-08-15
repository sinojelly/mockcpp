
#ifndef __MOCKCPP_TYPELESS_STUB_H
#define __MOCKCPP_TYPELESS_STUB_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

class Any;

class TypelessStub
{
public:
    virtual bool isCompleted() const = 0;
    virtual Any& invoke(void) = 0;
    virtual std::string toString(void) const = 0;

    virtual ~TypelessStub() {}
};

MOCKCPP_NS_END

#endif


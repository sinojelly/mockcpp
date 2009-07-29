
#ifndef __MOCKCPP_METHOD_NAME_GETTER_H
#define __MOCKCPP_METHOD_NAME_GETTER_H

#include <mockcpp.h>

#include <string>

MOCKCPP_NS_START

struct MethodNameGetter
{
    virtual std::string& getMethodName() const = 0;

    virtual ~MethodNameGetter() {}
};

MOCKCPP_NS_END

#endif


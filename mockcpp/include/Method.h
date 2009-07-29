
#ifndef __MOCKCPP_METHOD_H
#define __MOCKCPP_METHOD_H

#include <mockcpp.h>

#include <Any.h>
#include <RefAny.h>

#include <Invokable.h>

#include <string>

MOCKCPP_NS_START

class SelfDescribe;
class InvocationMockerNamespace;

/////////////////////////////////////////////
struct Method
    : public Invokable
{
    virtual std::string& getName() const = 0;

    virtual InvocationMockerNamespace* getNamespace() const = 0;

    virtual ~Method() {}
};

MOCKCPP_NS_END

#endif


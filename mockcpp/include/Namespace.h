
#ifndef __MOCKCPP_NAMESPACE_H
#define __MOCKCPP_NAMESPACE_H

#include <mockcpp.h>

#include <string>

MOCKCPP_NS_START

class InvocationMocker;

struct Namespace
{
    virtual ~Namespace() {}

    virtual InvocationMocker*
    getInvocationMocker(const std::string& name) = 0;
    
    virtual std::string& getName() const = 0;
};

MOCKCPP_NS_END

#endif


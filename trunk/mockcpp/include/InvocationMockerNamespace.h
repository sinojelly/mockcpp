
#ifndef __MOCKCPP_INVOCATION_MOCKER_NAMESPACE_H
#define __MOCKCPP_INVOCATION_MOCKER_NAMESPACE_H

#include <mockcpp.h>

MOCKCPP_NS_START

struct InvocationMockerNamespace
{
   virtual InvocationMocker* getInvocationMocker(const std::string& id) = 0;
   virtual std::string& getName(void) const = 0;

   virtual ~InvocationMockerNamespace() {}
};

MOCKCPP_NS_END

#endif


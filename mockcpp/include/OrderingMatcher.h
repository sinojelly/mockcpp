
#ifndef __MOCKCPP_ORDERING_MATCHER_H
#define __MOCKCPP_ORDERING_MATCHER_H

#include <mockcpp.h>
#include <Matcher.h>

MOCKCPP_NS_START

class InvocationMocker;

struct OrderingMatcher : public Matcher
{
   virtual ~OrderingMatcher() {}
   virtual bool isComplete(void) const = 0;
   virtual void setOrderingInvocationMocker(InvocationMocker* mocker) = 0;
};

MOCKCPP_NS_END

#endif


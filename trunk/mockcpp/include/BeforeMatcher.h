
#ifndef __MOCKCPP_BEFORE_MATCHER_H
#define __MOCKCPP_BEFORE_MATCHER_H

#include <mockcpp.h>
#include <OrderingMatcher.h>

#include <string>

MOCKCPP_NS_START

class InvocationMocker;
class Invocation;

class BeforeMatcher : public OrderingMatcher
{
public:

   BeforeMatcher(InvocationMocker* previousCall);

	bool matches(const Invocation& inv) const;

   void increaseInvoked(const Invocation& inv);

	std::string toString() const;

   bool isComplete(void) const;

   void setOrderingInvocationMocker(InvocationMocker* mocker);

private:

   InvocationMocker* previousCall;
};

MOCKCPP_NS_END

#endif


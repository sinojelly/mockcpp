
#ifndef __MOCKCPP_PENDING_MATCHER_H
#define __MOCKCPP_PENDING_MATCHER_H

#include <mockcpp.h>
#include <Matcher.h>

#include <string>

MOCKCPP_NS_START

class Invocation;
class OrderingMatcher;
class Namespace;
class InvocationMocker;

class PendingMatcher : public Matcher
{
public:

   PendingMatcher(OrderingMatcher* orderingMatcher
                 , Namespace* ns
                 , const std::string& identity
                 , InvocationMocker* ThisMocker);

	~PendingMatcher();

	bool matches(const Invocation& inv) const;

	void increaseInvoked(const Invocation& inv);

	std::string toString() const;

	void verify();

private:

	void setUpOrderingMatcher() const;

private:

   mutable OrderingMatcher* matcher;
	Namespace* scope;
   std::string id;
   InvocationMocker* mocker;
};

MOCKCPP_NS_END

#endif


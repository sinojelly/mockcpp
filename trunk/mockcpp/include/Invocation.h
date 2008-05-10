
#ifndef __MOCKCPP_INVOCATION_H
#define __MOCKCPP_INVOCATION_H

#include <mockcpp.h>

#include <RefAny.h>
#include <string>

MOCKCPP_NS_START

class InvocationImpl;

class Invocation
{
public:
	Invocation( const RefAny& p1 = RefAny()
             , const RefAny& p2 = RefAny()
             , const RefAny& p3 = RefAny()
             , const RefAny& p4 = RefAny()
             , const RefAny& p5 = RefAny()
             , const RefAny& p6 = RefAny());

	~Invocation();

	RefAny& getParameter(const unsigned int i) const;

   std::string toString(void) const;

private:
	InvocationImpl* This;
};

MOCKCPP_NS_END

#endif


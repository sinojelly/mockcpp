
#ifndef __MOCKCPP_METHOD_H
#define __MOCKCPP_METHOD_H

#include <mockcpp.h>
#include <InvocationMockBuilder.h>

MOCKCPP_NS_START

class Matcher;
class Stub;

struct Method
{
	~Method() {}
	virtual InvocationMockBuilder stubs() = 0;
	virtual InvocationMockBuilder expects(Matcher* matcher) = 0;
   virtual void setDefaultStub(Stub* stub) = 0;
};

MOCKCPP_NS_END

#endif


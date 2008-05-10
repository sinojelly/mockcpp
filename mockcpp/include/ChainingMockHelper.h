
#ifndef __MOCKCPP_CHAINING_MOCK_HELPER_H
#define __MOCKCPP_CHAINING_MOCK_HELPER_H

#include <mockcpp.h>
#include <ReturnStub.h>
#include <TypelessStubAdapter.h>
#include <IsEqual.h>
#include <OutBound.h>

MOCKCPP_NS_START

class Matcher;

Matcher* once();
Matcher* atLeast(unsigned int times);
Matcher* atMost(unsigned int times);
Matcher* exactly(unsigned int times);

template <typename T>
Constraint* eq(const T& val)
{
	return new IsEqual<T>(val);
}

template <typename T>
Constraint* outBound(const T& val, Constraint* constraint = 0)
{
   return new OutBound<T>(val, constraint);
}

template <typename T>
Stub* returnValue(const T& val)
{
	return new TypelessStubAdapter(new ReturnStub(val));
}

Matcher* never();

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_CHAINING_MOCK_HELPER_H
#define __MOCKCPP_CHAINING_MOCK_HELPER_H

#include <mockcpp.h>
#include <IsEqual.h>
#include <OutBound.h>
#include <Any.h>

MOCKCPP_NS_START

class Matcher;
class Stub;

Matcher* once();
Matcher* never();
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

Stub* returnValue(const Any& val);

Stub* returnObjectList( const Any& o01
                      , const Any& o02 = Any()
                      , const Any& o03 = Any()
                      , const Any& o04 = Any()
                      , const Any& o05 = Any()
                      , const Any& o06 = Any()
                      , const Any& o07 = Any()
                      , const Any& o08 = Any()
                      , const Any& o09 = Any()
                      , const Any& o10 = Any()
                      , const Any& o11 = Any()
                      , const Any& o12 = Any());



MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_IS_EQUAL_H
#define __MOCKCPP_IS_EQUAL_H

#include <mockcpp.h>
#include <Constraint.h>
#include <RefAny.h>
#include <Formatter.h>

MOCKCPP_NS_START

template <typename T>
class IsEqual : public Constraint
{
public:
    IsEqual(const T& expected)
      : expectedValue(expected)
    {}

    bool eval(const RefAny& val) const
    {
		if(!any_castable<T>(val)) return false;
      return any_cast<T>(val) == expectedValue;
    }

    std::string toString() const
    {
      return std::string("eq(") + 
             MOCKCPP_NS::toTypeAndValueString(expectedValue) +
             std::string(")");
    }

private:

    T expectedValue;
};

MOCKCPP_NS_END

#endif


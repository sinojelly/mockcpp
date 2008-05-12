
#ifndef __MOCKCPP_IS_MIRROR_H
#define __MOCKCPP_IS_MIRROR_H

#include <mockcpp.h>
#include <Constraint.h>
#include <RefAny.h>
#include <Formatter.h>

MOCKCPP_NS_START

template <typename T>
class IsMirror : public Constraint
{
public:
    IsMirror(const T& expected)
      : expectedValue(expected)
    {}

    bool eval(const RefAny& val) const
    {
		if(!any_castable<T>(val)) return false;
      return !memcmp((void*)&any_cast<T>(val), (void*)expectedValue, sizeof(T));
    }

    std::string toString() const
    {
      return std::string("mirror(") + 
             MOCKCPP_NS::toTypeAndValueString(expectedValue) +
             std::string(")");
    }

private:

    T expectedValue;
};

MOCKCPP_NS_END

#endif


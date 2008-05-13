
#ifndef __MOCKCPP_OUTBOUND_H
#define __MOCKCPP_OUTBOUND_H

#include <mockcpp.h>
#include <DecoratedConstraint.h>
#include <RefAny.h>
#include <Formatter.h>

MOCKCPP_NS_START

template <typename T>
class OutBound: public DecoratedConstraint
{
public:
    OutBound(const T& val, Constraint* constraint = 0)
      : ref(val), DecoratedConstraint(constraint)
    {}

    bool evalSelf(const RefAny& val) const
    {
      return const_cast<RefAny&>(val).changeValue(ref);
    }

    std::string getName() const
    {
      return "outBound";
    }

    std::string getTypeAndValueString() const
    {
      return toTypeAndValueString(ref);
    }

private:

    T ref;
};

MOCKCPP_NS_END

#endif


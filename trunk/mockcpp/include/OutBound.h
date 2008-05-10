
#ifndef __MOCKCPP_OUTBOUND_H
#define __MOCKCPP_OUTBOUND_H

#include <mockcpp.h>
#include <Constraint.h>
#include <RefAny.h>
#include <Formatter.h>

MOCKCPP_NS_START

template <typename T>
class OutBound: public Constraint
{
public:
    OutBound(const T& val, Constraint* constraint = 0)
      : ref(val), attachedConstraint(constraint)
    {}

    ~OutBound()
    {
      delete attachedConstraint;
    }

    bool eval(const RefAny& val) const
    {
      if(attachedConstraint != 0 &&
        !attachedConstraint->eval(val)) {
        return false;
      }

      return const_cast<RefAny&>(val).changeValue(ref);
    }

    std::string toString() const
    {
      return std::string("outBound(") + 
             MOCKCPP_NS::toTypeAndValueString(ref) +
             getAttachedConstraintString() +
             std::string(")");
    }

private:

    std::string getAttachedConstraintString() const
    {
      return (attachedConstraint == 0) ?
			"" : std::string(", ") + attachedConstraint->toString();
    }

private:
    Constraint* attachedConstraint;
    T ref;
};

MOCKCPP_NS_END

#endif


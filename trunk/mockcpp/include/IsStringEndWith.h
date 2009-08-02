
#ifndef __MOCKCPP_IS_STRING_END_WITH_H
#define __MOCKCPP_IS_STRING_END_WITH_H

#include <mockcpp.h>

#include <Constraint.h>
#include <StringConstraint.h>

MOCKCPP_NS_START

struct IsStringEndWith : public StringConstraint
{
    IsStringEndWith(const std::string& s)
       : StringConstraint(s)
    {}

    bool eval(const RefAny& value) const;
    std::string toString() const;
};

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_IS_STRING_CONTAINS_H
#define __MOCKCPP_IS_STRING_CONTAINS_H

#include <mockcpp.h>

#include <Constraint.h>
#include <StringConstraint.h>

MOCKCPP_NS_START

struct IsStringContains : public StringConstraint
{
    IsStringContains(const std::string& s)
       : StringConstraint(s)
    {}

    bool eval(const RefAny& value) const;
    std::string toString() const;
};

MOCKCPP_NS_END

#endif


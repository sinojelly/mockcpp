
#ifndef __MOCKCPP_STRING_CONSTRAINT_H
#define __MOCKCPP_STRING_CONSTRAINT_H

#include <mockcpp.h>
#include <Constraint.h>
#include <RefAny.h>

MOCKCPP_NS_START

class StringConstraint: public Constraint
{
public:
    StringConstraint(const std::string s)
      : str(s)
    {}

protected:
    char * tryToCastParameterToString(const RefAny& val) const;

protected:

   std::string str;
};

MOCKCPP_NS_END

#endif



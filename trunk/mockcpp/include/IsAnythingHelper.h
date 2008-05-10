
#ifndef __MOCKCPP_IS_ANYTHING_HELPER_H
#define __MOCKCPP_IS_ANYTHING_HELPER_H

#include <mockcpp.h>

MOCKCPP_NS_START

class Constraint;

Constraint* any();

bool isAnyConstraint(Constraint* c);

MOCKCPP_NS_END

#endif


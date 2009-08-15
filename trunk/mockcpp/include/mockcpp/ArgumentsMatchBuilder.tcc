
#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/ConstraintSet.h>

MOCKCPP_NS_START

template <typename Builder>
Builder&
ArgumentsMatchBuilder<Builder>::
with( Constraint* c01 
    , Constraint* c02
    , Constraint* c03
    , Constraint* c04
    , Constraint* c05
    , Constraint* c06
    , Constraint* c07
    , Constraint* c08
    , Constraint* c09
    , Constraint* c10
    , Constraint* c11
    , Constraint* c12
)
{
    getMocker()->addMatcher(
      new ConstraintSet(c01, c02, c03, c04, c05, c06,
                        c07, c08, c09, c10, c11, c12));
    return *this;
}


MOCKCPP_NS_END



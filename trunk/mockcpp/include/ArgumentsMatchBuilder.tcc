
#include <InvocationMocker.h>
#include <Constraint.h>
#include <ConstraintSet.h>

MOCKCPP_NS_START

template <typename Builder>
Builder&
ArgumentsMatchBuilder<Builder>::
with( Constraint* c1 
    , Constraint* c2
    , Constraint* c3
    , Constraint* c4
    , Constraint* c5
    , Constraint* c6)
{
    getMocker()->addMatcher( new ConstraintSet(c1, c2, c3, c4, c5, c6));
    return *this;
}


MOCKCPP_NS_END



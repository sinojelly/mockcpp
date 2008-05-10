
#ifndef __MOCKCPP_CONSTRAINT_SET_H
#define __MOCKCPP_CONSTRAINT_SET_H

#include <mockcpp.h>
#include <StatelessMatcher.h>
#include <IsAnythingHelper.h>

MOCKCPP_NS_START

class Invocation;
class Constraint;
class ConstraintSetImpl;

class ConstraintSet: public StatelessMatcher
{
public:
    ConstraintSet( Constraint* p1 = any()
                 , Constraint* p2 = any()
                 , Constraint* p3 = any()
                 , Constraint* p4 = any()
                 , Constraint* p5 = any()
                 , Constraint* p6 = any());

    ~ConstraintSet();

    virtual bool matches(const Invocation& inv) const;

    virtual std::string toString() const;
private:

    ConstraintSetImpl* This;
};

MOCKCPP_NS_END

#endif


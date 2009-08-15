
#ifndef __MOCKCPP_CONSTRAINT_SET_H
#define __MOCKCPP_CONSTRAINT_SET_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/StatelessMatcher.h>
#include <mockcpp/IsAnythingHelper.h>

MOCKCPP_NS_START

class Invocation;
class Constraint;
class ConstraintSetImpl;

class ConstraintSet: public StatelessMatcher
{
public:
    ConstraintSet( Constraint* p01 = any()
                 , Constraint* p02 = any()
                 , Constraint* p03 = any()
                 , Constraint* p04 = any()
                 , Constraint* p05 = any()
                 , Constraint* p06 = any()
                 , Constraint* p07 = any()
                 , Constraint* p08 = any()
                 , Constraint* p09 = any()
                 , Constraint* p10 = any()
                 , Constraint* p11 = any()
                 , Constraint* p12 = any()
    );

    ~ConstraintSet();

    virtual bool matches(const Invocation& inv) const;

    virtual std::string toString() const;

    virtual void verify(void);

private:

    ConstraintSetImpl* This;
};

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H
#define __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/IsAnythingHelper.h>
#include <mockcpp/DummyBuilder.h>

MOCKCPP_NS_START

class InvocationMocker;
class Constraint;

template <class Builder = DummyBuilder >
class ArgumentsMatchBuilder : public Builder
{
public:

    Builder& with( Constraint* c01 = any()
                 , Constraint* c02 = any()
                 , Constraint* c03 = any()
                 , Constraint* c04 = any()
                 , Constraint* c05 = any()
                 , Constraint* c06 = any()
                 , Constraint* c07 = any()
                 , Constraint* c08 = any()
                 , Constraint* c09 = any()
                 , Constraint* c10 = any()
                 , Constraint* c11 = any()
                 , Constraint* c12 = any()
    );

private:

    virtual InvocationMocker* getMocker() const = 0;

};

MOCKCPP_NS_END

#include <mockcpp/ArgumentsMatchBuilder.tcc>

#endif


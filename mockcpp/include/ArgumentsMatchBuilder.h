
#ifndef __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H
#define __MOCKCPP_ARGUMENTS_MATCH_BUILDER_H

#include <mockcpp.h>
#include <IsAnythingHelper.h>
#include <DummyBuilder.h>

MOCKCPP_NS_START

class InvocationMocker;
class Constraint;

template <class Builder = DummyBuilder >
class ArgumentsMatchBuilder : public Builder
{
public:

    Builder& with( Constraint* c1 = any()
                 , Constraint* c2 = any()
                 , Constraint* c3 = any()
                 , Constraint* c4 = any()
                 , Constraint* c5 = any()
                 , Constraint* c6 = any() );

private:

    virtual InvocationMocker* getMocker() const = 0;

};

MOCKCPP_NS_END

#include <ArgumentsMatchBuilder.tcc>

#endif


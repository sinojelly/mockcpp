
#ifndef __MOCKCPP_INVOCATION_MOCK_BUILDER_GETTER_H
#define __MOCKCPP_INVOCATION_MOCK_BUILDER_GETTER_H

#include <mockcpp.h>

#include <WorkingBuilder.h>
#include <DefaultBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
class Matcher;

///////////////////////////////////////////////
struct InvocationMockBuilderGetter
{
    virtual WorkingBuilder stubs() = 0;
    virtual WorkingBuilder expects(Matcher* matcher) = 0;
    virtual DefaultBuilder defaults() = 0;

    virtual ~InvocationMockBuilderGetter() {}
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif


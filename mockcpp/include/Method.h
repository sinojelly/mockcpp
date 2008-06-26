
#ifndef __MOCKCPP_METHOD_H
#define __MOCKCPP_METHOD_H

#include <mockcpp.h>
#include <InvocationMockBuilder.h>
#include <AfterMatchBuilder.h>
#include <BeforeMatchBuilder.h>
#include <IdentityBuilder.h>
#include <StubBuilder.h>
#include <ArgumentsMatchBuilder.h>

MOCKCPP_NS_START

class Matcher;

///////////////////////////////////////////////
typedef InvocationMockBuilder< 
          BeforeMatchBuilder<
            ArgumentsMatchBuilder<
              AfterMatchBuilder<
                StubBuilder< 
                  IdentityBuilder
                >
              >
            >
          >
        > WorkingBuilder;

///////////////////////////////////////////////
typedef InvocationMockBuilder< 
          ArgumentsMatchBuilder<
             StubBuilder<>
          >
        > DefaultBuilder;

///////////////////////////////////////////////
struct Method
{
    virtual WorkingBuilder stubs() = 0;
    virtual WorkingBuilder expects(Matcher* matcher) = 0;
    virtual DefaultBuilder defaults() = 0;

    ~Method() {}
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif


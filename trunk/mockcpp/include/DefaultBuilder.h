
#ifndef __MOCKCPP_DEFAULT_BUIDLER_H_
#define __MOCKCPP_DEFAULT_BUIDLER_H_

#include <mockcpp.h>

#include <InvocationMockBuilder.h>
#include <CallerMatchBuilder.h>
#include <ArgumentsMatchBuilder.h>
#include <StubBuilder.h>
#include <MoreStubBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
typedef InvocationMockBuilder< 
         CallerMatchBuilder<
          ArgumentsMatchBuilder<
           StubBuilder<
            MoreStubBuilder<>
           >
          >
         >
        > DefaultBuilder;

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif


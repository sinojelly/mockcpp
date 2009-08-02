
#ifndef __MOCKCPP_WORKING_BUILDER_H
#define __MOCKCPP_WORKING_BUILDER_H

#include <mockcpp.h>

#include <InvocationMockBuilder.h>
#include <CallerMatchBuilder.h>
#include <BeforeMatchBuilder.h>
#include <ArgumentsMatchBuilder.h>
#include <AfterMatchBuilder.h>
#include <StubBuilder.h>
#include <MoreStubBuilder.h>
#include <IdentityBuilder.h>

MOCKCPP_NS_START

///////////////////////////////////////////////
typedef InvocationMockBuilder<
          CallerMatchBuilder<
           BeforeMatchBuilder<
            ArgumentsMatchBuilder<
             AfterMatchBuilder<
              StubBuilder< 
               MoreStubBuilder<
                IdentityBuilder
               >
              >
             >
            >
           >
          >
         > WorkingBuilder;

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif


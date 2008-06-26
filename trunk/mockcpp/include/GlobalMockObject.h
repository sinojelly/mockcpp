
#ifndef __MOCKCPP_GLOBAL_MOCK_OBJECT_H
#define __MOCKCPP_GLOBAL_MOCK_OBJECT_H

#include <mockcpp.h>

#include <ChainableMockObject.h>

MOCKCPP_NS_START

struct GlobalMockObject
{
   static void verify();
   static void reset();

   static ChainableMockObject instance;
};

MOCKCPP_NS_END

#endif


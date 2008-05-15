
#ifndef __MOCKCPP_HPP_
#define __MOCKCPP_HPP_

#include <mockcpp.h>
#include <ChainableMockObject.h>
#include <ChainingMockHelper.h>
#include <MockCppNsHelper.h>

using namespace mockcpp;

#define __MOCKCPP_MOCK_CLASS_NAME(CLASS_) Mock ## CLASS_

/////////////////////////////////////////////////////////////////
#define MOCKCPP_MOCK_CLASS_DEF(NS_, CLASS_) \
class __MOCKCPP_MOCK_CLASS_NAME(CLASS_) \
    : public CLASS_ \
    , public MOCKCPP_NS::ChainableMockObject \
{ \
public: \
   __MOCKCPP_MOCK_CLASS_NAME(CLASS_)() \
      : MOCKCPP_NS::ChainableMockObject(#CLASS_, MOCKCPP_GET_NS_OBJ(NS_)) \
   {}

#define MOCKCPP_MOCK_CLASS_DEF_END };

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD0(RT_, METHOD_, CONST_) \
   RT_ METHOD_(void) CONST_ { return invoke<RT_>(#METHOD_)(); }

#define MOCKCPP_METHOD_DEF0(RT_, METHOD_) \
   __MOCKCPP_METHOD0(RT_, METHOD_, )

#define MOCKCPP_CONST_METHOD0(RT_, METHOD_) \
   __MOCKCPP_METHOD0(RT_, METHOD_, const)

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD1(RT_, METHOD_, T1, CONST_) \
   RT_ METHOD_(T1 p1) CONST_ { return invoke<RT_>(#METHOD_)(p1); }

#define MOCKCPP_METHOD1(RT_, METHOD_, T1) \
   __MOCKCPP_METHOD1(RT_, METHOD_, T1, )

#define MOCKCPP_CONST_METHOD1(RT_, METHOD_, T1) \
   __MOCKCPP_METHOD1(RT_, METHOD_, T1, const)

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD_DEF2(RT_, METHOD_, T1, T2, CONST_) \
   RT_ METHOD_(T1 p1, T2 p2) CONST_ { return invoke<RT_>(#METHOD_)(p1, p2); }

#define MOCKCPP_METHOD2(RT_, METHOD_, T1, T2) \
   __MOCKCPP_METHOD_DEF2(RT_, METHOD_, T1, T2, )

#define MOCKCPP_CONST_METHOD2(RT_, METHOD_, T1, T2) \
   __MOCKCPP_METHOD_DEF2(RT_, METHOD_, T1, T2, const)

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD_DEF3(RT_, METHOD_, T1, T2, T3, CONST_) \
   RT_ METHOD_(T1 p1, T2 p2, T3 p3) CONST_ \
   { \
     return invoke<RT_>(#METHOD_)(p1, p2, p3); \
   }

#define MOCKCPP_METHOD_DEF3(RT_, METHOD_, T1, T2, T3) \
   __MOCKCPP_METHOD_DEF3(RT_, METHOD_, T1, T2, T3, )

#define MOCKCPP_METHOD_DEF3_CONST(RT_, METHOD_, T1, T2, T3) \
   __MOCKCPP_METHOD_DEF3(RT_, METHOD_, T1, T2, T3, const)

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD_DEF4(RT_, METHOD_, T1, T2, T3, T4, CONST_) \
   RT_ METHOD_(T1 p1, T2 p2, T3 p3, T4 p4) CONST_ \
   { \
     return invoke<RT_>(#METHOD_)(p1, p2, p3, p4); \
   }

#define MOCKCPP_METHOD4(RT_, METHOD_, T1, T2, T3, T4) \
   __MOCKCPP_METHOD_DEF4(RT_, METHOD_, T1, T2, T3, T4, )

#define MOCKCPP_CONST_METHOD4(RT_, METHOD_, T1, T2, T3, T4) \
   __MOCKCPP_METHOD_DEF4(RT_, METHOD_, T1, T2, T3, T4, const)

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD_DEF5(RT_, METHOD_, T1, T2, T3, T4, T5, CONST_) \
   RT_ METHOD_(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5) CONST_ \
   { \
     return invoke<RT_>(#METHOD_)(p1, p2, p3, p4, p5); \
   }

#define MOCKCPP_METHOD5(RT_, METHOD_, T1, T2, T3, T4, T5) \
   __MOCKCPP_METHOD_DEF5(RT_, METHOD_, T1, T2, T3, T4, T5, )

#define MOCKCPP_CONST_METHOD5(RT_, METHOD_, T1, T2, T3, T4, T5) \
   __MOCKCPP_METHOD_DEF5(RT_, METHOD_, T1, T2, T3, T4, T5, const)

/////////////////////////////////////////////////////////////////
#define __MOCKCPP_METHOD_DEF6(RT_, METHOD_, T1, T2, T3, T4, T5, T6, CONST_) \
   RT_ METHOD_(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6) CONST_ \
   { \
     return invoke<RT_>(#METHOD_)(p1, p2, p3, p4, p5, p6); \
   }

#define MOCKCPP_METHOD6(RT_, METHOD_, T1, T2, T3, T4, T5, T6) \
   __MOCKCPP_METHOD_DEF6(RT_, METHOD_, T1, T2, T3, T4, T5, T6, )

#define MOCKCPP_CONST_METHOD6(RT_, METHOD_, T1, T2, T3, T4, T5, T6) \
   __MOCKCPP_METHOD_DEF6(RT_, METHOD_, T1, T2, T3, T4, T5, T6, const)

////////////////////////////////////////////////////////////////

#endif



#ifndef __MOCKCPP_CMOCK_H
#define __MOCKCPP_CMOCK_H

#include <mockcpp.h>
#include <ChainableMockObject.h>
#include <RefAny.h>
#include <GlobalMockNs.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////////
#define MOCKER(M) MOCKCPP_GET_NS_OBJ(Global)->method(#M)

#define MOCKABLE(method) mock_##method

//////////////////////////////////////////////////////////////////////
#define MOCK_METHOD0_DECL(method, RT) \
RT MOCKABLE(method)(void);

#define MOCK_METHOD0_DEF(method, RT) \
RT MOCKABLE(method)(void) \
{ \
    return MOCKCPP_GET_NS_OBJ(Global)->invoke<RT>(#method)(); \
}

//////////////////////////////////////////////////////////////////////
#define MOCK_METHOD1_DECL(method, RT, T1) \
RT MOCKABLE(method)(T1);

#define MOCK_METHOD1_DEF(method, RT, T1) \
RT MOCKABLE(method)(T1 p1) \
{ \
    return MOCKCPP_GET_NS_OBJ(Global)->invoke<RT>(#method)(p1); \
}

//////////////////////////////////////////////////////////////////////
#define MOCK_METHOD2_DECL(method, RT, T1, T2) \
RT MOCKABLE(method)(T1, T2);

#define MOCK_METHOD2_DEF(method, RT, T1, T2) \
RT MOCKABLE(method)(T1 p1, T2 p2) \
{ \
    return MOCKCPP_GET_NS_OBJ(Global)->invoke<RT>(#method)(p1, p2); \
}

//////////////////////////////////////////////////////////////////////
#define MOCK_METHOD3_DECL(method, RT, T1, T2, T3) \
RT MOCKABLE(method)(T1, T2, T3);

#define MOCK_METHOD3_DEF(method, RT, T1, T2, T3) \
RT MOCKABLE(method)(T1 p1, T2 p2, T3 p3) \
{ \
    return MOCKCPP_GET_NS_OBJ(Global)->invoke<RT>(#method)(p1, p2, p3); \
}

//////////////////////////////////////////////////////////////////////
#define MOCK_METHOD4_DECL(method, RT, T1, T2, T3, T4) \
RT MOCKABLE(method)(T1, T2, T3, T4);

#define MOCK_METHOD4_DEF(method, RT, T1, T2, T3, T4) \
RT MOCKABLE(method)(T1 p1, T2 p2, T3 p3, T4 p4) \
{ \
    return MOCKCPP_GET_NS_OBJ(Global)->invoke<RT>(#method)(p1, p2, p3, p4); \
}

//////////////////////////////////////////////////////////////////////
#define MOCK_METHOD_ANY_DECL(method, RT) \
RT MOCKABLE(method)(const RefAny& p01 = RefAny(), const RefAny& p02 = RefAny(), const RefAny& p03 = RefAny(), \
                    const RefAny& p04 = RefAny(), const RefAny& p05 = RefAny(), const RefAny& p06 = RefAny(), \
	                 const RefAny& p07 = RefAny(), const RefAny& p08 = RefAny(), const RefAny& p09 = RefAny(), \
                    const RefAny& p10 = RefAny(), const RefAny& p11 = RefAny(), const RefAny& p12 = RefAny());

#define MOCK_METHOD_ANY_DEF(method, RT) \
RT MOCKABLE(method)(const RefAny& p01, const RefAny& p02, const RefAny& p03, \
                    const RefAny& p04, const RefAny& p05, const RefAny& p06, \
	                 const RefAny& p07, const RefAny& p08, const RefAny& p09, \
                    const RefAny& p10, const RefAny& p11, const RefAny& p12) \
{ \
    return MOCKCPP_GET_NS_OBJ(Global)-> \
                invoke<RT>(#method)(p01, p02, p03, \
                                    p04, p05, p06, \
                                    p07, p08, p09, \
                                    p10, p11, p12); \
}

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_DELEGATED_METHOD_H
#define __MOCKCPP_DELEGATED_METHOD_H

#include <mockcpp.h>

#include <ArgumentsList.h>
#include <VirtualTable.h>
#include <ChainableMockMethod.h>
#include <ArgumentsMacroHelpers.h>
#include <IndexInvokableGetter.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////
template <int VPTRIndex, int VTBLIndex, typename ArgumentsList>
struct DelegatedMethod;

#define MOCKCPP_DELEGATED_METHOD_DEF(n) \
template <int VPTRIndex, int VTBLIndex, typename R DECL_TEMPLATE_ARGS(n)> \
struct DelegatedMethod<VPTRIndex, VTBLIndex, ArgumentsList<R DECL_REST_ARGS(n)> > \
{ \
   enum { IsConst = 0 }; \
   enum { NumberOfParameters = n }; \
	R operator()(DECL_PARAMS_LIST(n)) \
   { \
      IndexInvokableGetter* getter = VirtualTable::getInvokableGetter(this, VPTRIndex); \
      return ChainableMockMethod<R>(getter->getInvokable(VPTRIndex, VTBLIndex))("" DECL_REST_PARAMS(n)); \
   } \
}

#define MOCKCPP_CONST_DELEGATED_METHOD_DEF(n) \
template <int VPTRIndex, int VTBLIndex, typename R DECL_TEMPLATE_ARGS(n)> \
struct DelegatedMethod<VPTRIndex, VTBLIndex, ArgumentsListConst<R DECL_REST_ARGS(n)> > \
{ \
   enum { IsConst = 1 }; \
   enum { NumberOfParameters = n }; \
	R operator()(DECL_PARAMS_LIST(n)) \
   { \
      IndexInvokableGetter* getter = VirtualTable::getInvokableGetter(this, VPTRIndex); \
      return ChainableMockMethod<R>(getter->getInvokable(VPTRIndex, VTBLIndex))("" DECL_REST_PARAMS(n)); \
   } \
}

MOCKCPP_DELEGATED_METHOD_DEF(0);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(0);

MOCKCPP_DELEGATED_METHOD_DEF(1);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(1);

MOCKCPP_DELEGATED_METHOD_DEF(2);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(2);

MOCKCPP_DELEGATED_METHOD_DEF(3);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(3);

MOCKCPP_DELEGATED_METHOD_DEF(4);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(4);

MOCKCPP_DELEGATED_METHOD_DEF(5);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(5);

MOCKCPP_DELEGATED_METHOD_DEF(6);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(6);

#if MOCKCPP_MAX_PARAMETERS > 6
MOCKCPP_DELEGATED_METHOD_DEF(7);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(7);
#endif

#if MOCKCPP_MAX_PARAMETERS > 7
MOCKCPP_DELEGATED_METHOD_DEF(8);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(8);
#endif

#if MOCKCPP_MAX_PARAMETERS > 8
MOCKCPP_DELEGATED_METHOD_DEF(9);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(9);
#endif

#if MOCKCPP_MAX_PARAMETERS > 9
MOCKCPP_DELEGATED_METHOD_DEF(10);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(10);
#endif

#if MOCKCPP_MAX_PARAMETERS > 10
MOCKCPP_DELEGATED_METHOD_DEF(11);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(11);
#endif

#if MOCKCPP_MAX_PARAMETERS > 11
MOCKCPP_DELEGATED_METHOD_DEF(12);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(12);
#endif

#if MOCKCPP_MAX_PARAMETERS > 12
MOCKCPP_DELEGATED_METHOD_DEF(13);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(13);
#endif

#if MOCKCPP_MAX_PARAMETERS > 13
MOCKCPP_DELEGATED_METHOD_DEF(14);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(14);
#endif

#if MOCKCPP_MAX_PARAMETERS > 14
MOCKCPP_DELEGATED_METHOD_DEF(15);
MOCKCPP_CONST_DELEGATED_METHOD_DEF(15);
#endif

MOCKCPP_NS_END

#endif


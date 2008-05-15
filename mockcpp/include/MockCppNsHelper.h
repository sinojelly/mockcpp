
#ifndef __MOCKCPP_NS_HELPER_H
#define __MOCKCPP_NS_HELPER_H

#define __MOCKCPP_NS_OBJ(NS_) NS_##MockContext

////////////////////////////////////////////////////////////////
#define MOCKCPP_GET_NS_OBJ(NS_) get ## NS_ ## MockContext ()

////////////////////////////////////////////////////////////////
#define MOCKCPP_NS_OBJ_VERIFY_AND_RESET(NS_) \
     verifyAndReset ## NS_ ## MockContext ()

////////////////////////////////////////////////////////////////
#define MOCKCPP_NS_OBJ_RESET(NS_) \
     reset ## NS_ ## MockContext ()

////////////////////////////////////////////////////////////////
#define MOCKCPP_NS_OBJ_DECL(NS_) \
ChainableMockObject* MOCKCPP_GET_NS_OBJ(NS_); \
void MOCKCPP_NS_OBJ_VERIFY_AND_RESET(NS_); \
void MOCKCPP_NS_OBJ_RESET(NS_)


////////////////////////////////////////////////////////////////
#define __MOCKCPP_NS_OBJ_NAME(NS_) static_ ## NS_ ## _object

////////////////////////////////////////////////////////////////
#define __MOCKCPP_CHECK_NS_OBJ(NS_) \
   if (__MOCKCPP_NS_OBJ_NAME(NS_) == 0) \
   { \
      return; \
   } 

////////////////////////////////////////////////////////////////
#define MOCKCPP_NS_OBJ_DEF(NS_, NS_STR_, PNS_) \
namespace { ChainableMockObject* __MOCKCPP_NS_OBJ_NAME(NS_) = 0; } \
ChainableMockObject* MOCKCPP_GET_NS_OBJ(NS_) \
{ \
   if (__MOCKCPP_NS_OBJ_NAME(NS_) == 0) \
   { \
     __MOCKCPP_NS_OBJ_NAME(NS_) = new ChainableMockObject(NS_STR_, PNS_); \
   } \
   return __MOCKCPP_NS_OBJ_NAME(NS_); \
} \
void MOCKCPP_NS_OBJ_VERIFY_AND_RESET(NS_) \
{ \
   __MOCKCPP_CHECK_NS_OBJ(NS_) \
   try { \
      __MOCKCPP_NS_OBJ_NAME(NS_)->verify(); \
      __MOCKCPP_NS_OBJ_NAME(NS_)->reset(); \
   } \
   catch(...) \
   { \
      __MOCKCPP_NS_OBJ_NAME(NS_)->reset(); \
      throw; \
   } \
} \
void MOCKCPP_NS_OBJ_RESET(NS_) \
{ \
   __MOCKCPP_CHECK_NS_OBJ(NS_) \
   __MOCKCPP_NS_OBJ_NAME(NS_)->reset(); \
}

#endif


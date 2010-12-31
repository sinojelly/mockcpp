
#ifndef __MOCKCPP_API_HOOK_FUNCTOR_H__
#define __MOCKCPP_API_HOOK_FUNCTOR_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/GlobalMockObject.h>

MOCKCPP_NS_START

//      return GlobalMockObject::instance.invoke<R>(apiAddress) \
                                (empty_caller DECL_REST_PARAMS(n)); \
/////////////////////////////////////////////////////
template <typename F, unsigned int Seq>
struct ApiHookFunctor
{
};

const std::string empty_caller("");
#define MOCKCPP_API_HOOK_FUNCTOR_DEF(n) \
template <typename R DECL_TEMPLATE_ARGS(n), unsigned int Seq> \
struct ApiHookFunctor<R(DECL_ARGS(n)), Seq> \
{ \
private: \
   typedef R F (DECL_ARGS(n)); \
 \
   static R hook(DECL_PARAMS_LIST(n)) \
   { \
      return GlobalMockObject::instance.invoke<R>(apiAddress) \
                                (empty_caller DECL_REST_PARAMS(n)); \
   } \
 \
   static bool applied(F* api) \
   { return apiAddress == reinterpret_cast<void*>(api); } \
 \
   static void* getHook() \
   { return reinterpret_cast<void*>(hook); } \
 \
public: \
 \
   static void* getApiHook(F* api) \
   { return applied(api) ? getHook() : 0; } \
 \
   static void* applyApiHook(F* api) \
   { \
      if(apiAddress != 0) return 0; \
      apiAddress = reinterpret_cast<void*>(api); \
      return getHook(); \
   } \
 \
   static bool freeApiHook(void* hook) \
   { \
       if(getHook() != hook) return false; \
       apiAddress = 0; \
       return true; \
   } \
private: \
   static void* apiAddress; \
}; \
template <typename R DECL_TEMPLATE_ARGS(n), unsigned int Seq> \
void* ApiHookFunctor<R(DECL_ARGS(n)), Seq>::apiAddress = 0 

MOCKCPP_API_HOOK_FUNCTOR_DEF(0);
MOCKCPP_API_HOOK_FUNCTOR_DEF(1);
MOCKCPP_API_HOOK_FUNCTOR_DEF(2);
MOCKCPP_API_HOOK_FUNCTOR_DEF(3);
MOCKCPP_API_HOOK_FUNCTOR_DEF(4);
MOCKCPP_API_HOOK_FUNCTOR_DEF(5);
MOCKCPP_API_HOOK_FUNCTOR_DEF(6);
MOCKCPP_API_HOOK_FUNCTOR_DEF(7);
MOCKCPP_API_HOOK_FUNCTOR_DEF(8);
MOCKCPP_API_HOOK_FUNCTOR_DEF(9);
MOCKCPP_API_HOOK_FUNCTOR_DEF(10);
MOCKCPP_API_HOOK_FUNCTOR_DEF(11);
MOCKCPP_API_HOOK_FUNCTOR_DEF(12);

MOCKCPP_NS_END

#endif


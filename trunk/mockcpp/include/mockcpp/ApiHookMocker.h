
#ifndef __MOCKCPP_API_HOOK_MOCKER_H__
#define __MOCKCPP_API_HOOK_MOCKER_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/CApiHookFunctorX64.h>
#include <mockcpp/GlobalMockObject.h>

MOCKCPP_NS_START

template <typename API>
struct ApiHookMocker
{
    static InvocationMockBuilderGetter mock(const std::string& name, const void* api)
    {
         return MOCKCPP_NS::GlobalMockObject::instance.method
                 ( name
                 , api
                 , (const void *)CApiHookFunctor<API>::hook
                 , (const void *)CApiHookFunctor<API>::dummy_hook
                 , (const void *)CApiHookFunctor<API>::real_hook);
    }
};

MOCKCPP_NS_END

#endif


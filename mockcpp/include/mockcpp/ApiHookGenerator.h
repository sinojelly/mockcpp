
#ifndef __MOCKCPP_API_HOOK_GENERATOR_H__
#define __MOCKCPP_API_HOOK_GENERATOR_H__

#include <mockcpp/ApiHookFunctor.h>

MOCKCPP_NS_START

/////////////////////////////////////////////////////////////////
template <typename F, unsigned int Seq>
struct ApiHookGenerator
{
    static void* findApiHook(F* api)
    {
        void* hook;

        (hook = ApiHookFunctor<F, Seq>::getApiHook(api)) ||
        (hook = ApiHookGenerator<F, Seq-1>::findApiHook(api));

        return hook;
    }

    static void* appyApiHook(F* api)
    {
       void* hook;

       (hook = ApiHookFunctor<F, Seq>::applyApiHook(api)) ||
       (hook = ApiHookGenerator<F, Seq-1>::appyApiHook(api));

       return hook;
    }

    static bool freeApiHook(void* hook)
    {
        return 
        (ApiHookFunctor<F, Seq>::freeApiHook(hook)) ||
        (ApiHookGenerator<F, Seq-1>::freeApiHook(hook));
    }

private:

};

/////////////////////////////////////////////////////////////////
template <typename F>
struct ApiHookGenerator<F, 0>
{
    static void* findApiHook(F* api)
    { return 0; }

    static void* appyApiHook(F* api)
    { return 0; }

    static bool freeApiHook(void* hook)
    { return true; }
};

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif


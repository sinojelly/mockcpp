
#ifndef __MOCKCPP_C_API_HOOK_H__
#define __MOCKCPP_C_API_HOOK_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ApiHook.h>

MOCKCPP_NS_START

struct ArchApiHook;
struct PageAllocator;

struct ApiHook
{
    ApiHook(void* pfnOld, void* pfnNew);
    ~ApiHook();

private:
    PageAllocator *allocator;
    ArchApiHook* hooker;
};

MOCKCPP_NS_END

#endif

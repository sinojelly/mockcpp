
#ifndef __MOCKCPP_C_API_HOOK_H__
#define __MOCKCPP_C_API_HOOK_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ApiHook.h>

MOCKCPP_NS_START

struct Arch32ApiHook;
struct PageAllocator;

struct CApiHook
{
	CApiHook(ApiHook::Address pfnOld, ApiHook::Address pfnNew);
	~CApiHook();

private:
    PageAllocator *allocator;
	Arch32ApiHook* hooker;
};

MOCKCPP_NS_END

#endif

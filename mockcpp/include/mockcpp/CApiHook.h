
#ifndef __MOCKCPP_C_API_HOOK_H__
#define __MOCKCPP_C_API_HOOK_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

struct CApiHookImpl;

struct CApiHook
{
    typedef void* Address;

    CApiHook(Address pfnOld, Address pfnNew);
	~CApiHook();

private:
	CApiHookImpl* This;
};

MOCKCPP_NS_END

#endif

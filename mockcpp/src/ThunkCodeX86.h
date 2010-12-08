
#ifndef __MOCKCPP_THUNK_CODE_X64_UNIX_H__
#define __MOCKCPP_THUNK_CODE_X64_UNIX_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

#define ZERO_ADDR 0x00, 0x00, 0x00, 0x00

const unsigned char thunkTemplate[] =
{
    0x58, // pop eax
    0x59, // pop ecx
    0xB9, ZERO_ADDR, // mov ecx, api
    0x51, // push ecx
    0x50, // push eax
    0xB8, ZERO_ADDR, // mov eax, stub
    0xFF, 0xE0 // jmp eax
};

struct ThunkCode
{
   static void copyTo(void* thunk, const void* api, const void* stub)
   {
      ::memcpy(thunk, thunkTemplate, sizeof(thunkTemplate));
      *(uintptr_t*)((unsigned char*)thunk+3)  = (uintptr_t)api;
      *(uintptr_t*)((unsigned char*)thunk+10) = (uintptr_t)stub;
   }

   static size_t size()
   { return sizeof(thunkTemplate); }
};

MOCKCPP_NS_END

#endif


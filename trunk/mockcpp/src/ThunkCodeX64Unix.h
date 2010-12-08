
#ifndef __MOCKCPP_THUNK_CODE_X64_UNIX_H__
#define __MOCKCPP_THUNK_CODE_X64_UNIX_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

#define ZERO_ADDR 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

const unsigned char thunkTemplate[] =
{
    0x48, 0xBF, ZERO_ADDR,   // mov rdi, api
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, ZERO_ADDR // jmp stub
};

struct ThunkCode
{
   static void copyTo(void* thunk, const void* api, const void* stub)
   {
      ::memcpy(thunk, thunkTemplate, sizeof(thunkTemplate));
      *(uintptr_t*)((unsigned char*)thunk+2) = (uintptr_t)api;
      *(uintptr_t*)((unsigned char*)thunk+16) = (uintptr_t)stub;
   }

   static size_t size()
   { return sizeof(thunkTemplate); }
};

MOCKCPP_NS_END

#endif


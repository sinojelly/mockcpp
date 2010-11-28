/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>
                                   <Chen Guodong: sinojelly@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#if BUILD_FOR_X64


#ifndef __MOCKCPP_THUNK_CODE_X64_H__
#define __MOCKCPP_THUNK_CODE_X64_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ArgumentsMacroHelpers.h>
#include <mockcpp/ThunkCode.h>

MOCKCPP_NS_START

/*
x64 use    rcx, rdx, r8, r9 as parameter register, the others are on the stack
      caller  reserve (number of parameter + return value) * 8 when call a function.
      it also ok reserve more bytes in stack, so we assume return value always exists.
      so at most reserve 70h bytes in stack.(>=(12+1+1)*8, max 12 param, 1 return value, 1 old_addr)
      and , reserve (n + 2) * 8 bytes

*/    


template<typename F> 
struct ThunkCodeTemplate;


#define THUNK_CODE_TEMPLATE_DEF(n) \
template<typename R DECL_TEMPLATE_ARGS(n)> \
struct ThunkCodeTemplate<R(DECL_ARGS(n))> : public ThunkCode \
{ \
    const void *thunkCodeStart() const \
    { \
        return thunkCodeTemplate; \
    } \
    \
    size_t thunkCodeLength() const \
    { \
        return sizeof(thunkCodeTemplate); \
    } \
    \
    size_t oldAddrOffset() const \
    { \
        return 9; \
    } \
    \
    size_t newAddrOffset() const \
    { \
        return 4; \
    }\
}

template<typename R DECL_TEMPLATE_ARGS(0)>
struct ThunkCodeTemplate<R(DECL_ARGS(0))> : public ThunkCode 
{ 
    const void *thunkCodeStart() const 
    {
        const static unsigned char thunkCodeTemplate[] =
        {
            0x40, 0x57, // push rdi
             // sub rsp, 10h         
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xD0, 0xFF, // call rax
             // move return value to the stack caller reserved
             // add rsp, 10h
            0x5F,       // pop rdi
            0xC3        // ret        
        };
        return thunkCodeTemplate; 
    } 
    
    size_t thunkCodeLength() const 
    { 
        return sizeof(thunkCodeTemplate); 
    } 
    
    size_t oldAddrOffset() const 
    { 
        return 9; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 4; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(1)>
struct ThunkCodeTemplate<R(DECL_ARGS(1))> : public ThunkCode 
{ 
    const void *thunkCodeStart() const 
    {
        // todo: param1 is in rcx, move it to rdx, then put old_addr in rcx,   stack is 3 * 8
        const static unsigned char thunkCodeTemplate[] =
        {
            0x40, 0x57, // push rdi
             // sub rsp, 18h         
             // mov rdx, rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xD0, 0xFF, // call rax
             // move return value to the stack caller reserved
             // add rsp, 18h
            0x5F,       // pop rdi
            0xC3        // ret        
        };
        return thunkCodeTemplate; 
    } 
    
    size_t thunkCodeLength() const 
    { 
        return sizeof(thunkCodeTemplate); 
    } 
    
    size_t oldAddrOffset() const 
    { 
        return 9; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 4; 
    }
};

template<typename R DECL_TEMPLATE_ARGS(2)>
struct ThunkCodeTemplate<R(DECL_ARGS(2))> : public ThunkCode 
{ 
    const void *thunkCodeStart() const 
    {
        const static unsigned char thunkCodeTemplate[] =
        {
            0x40, 0x57, // push rdi
             // sub rsp, 20h         
             // mov r8, rdx
             // mov rd, rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xD0, 0xFF, // call rax
             // move return value to the stack caller reserved
             // add rsp, 20h
            0x5F,       // pop rdi
            0xC3        // ret        
        };
        return thunkCodeTemplate; 
    } 
    
    size_t thunkCodeLength() const 
    { 
        return sizeof(thunkCodeTemplate); 
    } 
    
    size_t oldAddrOffset() const 
    { 
        return 9; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 4; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(3)>
struct ThunkCodeTemplate<R(DECL_ARGS(3))> : public ThunkCode 
{ 
    const void *thunkCodeStart() const 
    {
        const static unsigned char thunkCodeTemplate[] =
        {
            0x40, 0x57, // push rdi
             // sub rsp, 28h         
             // mov r9, r8
             // mov r8, rdx
             // mov rdx, rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xD0, 0xFF, // call rax
             // move return value to the stack caller reserved
             // add rsp, 28h
            0x5F,       // pop rdi
            0xC3        // ret        
        };
        return thunkCodeTemplate; 
    } 
    
    size_t thunkCodeLength() const 
    { 
        return sizeof(thunkCodeTemplate); 
    } 
    
    size_t oldAddrOffset() const 
    { 
        return 9; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 4; 
    }
};

template<typename R DECL_TEMPLATE_ARGS(4)>
struct ThunkCodeTemplate<R(DECL_ARGS(4))> : public ThunkCode 
{ 
    const void *thunkCodeStart() const 
    {
        const static unsigned char thunkCodeTemplate[] =
        {
            0x40, 0x57, // push rdi
             // sub rsp, 30h 
             // mov [mem], r9
             // mov r9, r8
             // mov r8, rdx
             // mov rdx, rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xD0, 0xFF, // call rax
             // move return value to the stack caller reserved
             // add rsp, 30h
            0x5F,       // pop rdi
            0xC3        // ret        
        };
        return thunkCodeTemplate; 
    } 
    
    size_t thunkCodeLength() const 
    { 
        // assert  sizeof(thunkCodeTemplate) < 100  => use static assert or typedef err[100-sizeof]
        return sizeof(thunkCodeTemplate); 
    } 
    
    size_t oldAddrOffset() const 
    { 
        return 9; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 4; 
    }
};


THUNK_CODE_TEMPLATE_DEF(5);
THUNK_CODE_TEMPLATE_DEF(6);
THUNK_CODE_TEMPLATE_DEF(7);
THUNK_CODE_TEMPLATE_DEF(8);
THUNK_CODE_TEMPLATE_DEF(9);
THUNK_CODE_TEMPLATE_DEF(10);
THUNK_CODE_TEMPLATE_DEF(11);
THUNK_CODE_TEMPLATE_DEF(12);


MOCKCPP_NS_END

#endif

#endif


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


template<typename R DECL_TEMPLATE_ARGS(0)>
struct ThunkCodeTemplate<R(DECL_ARGS(0))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(0))>()
    {
        const static unsigned char thunkCode[] =
        {
            0x40, 0x57, // push rdi
            0x48, 0x8b, 0xfc,  // mov rdi,rsp
            0x48, 0x83, 0xec, 0x10, // sub rsp, 10h 
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
             // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x10, // add rsp, 10h
            0x5F,       // pop rdi
            0xC3        // ret        
        };

        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    } 
    
    size_t oldAddrOffset() const 
    { 
        return 21; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 11; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(1)>
struct ThunkCodeTemplate<R(DECL_ARGS(1))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(1))>()
    {
        const static unsigned char thunkCode[] =
        {
            0x40, 0x57, // push rdi
            0x48, 0x8b, 0xfc,  // mov rdi,rsp
            0x48, 0x83, 0xec, 0x18, // sub rsp, 18h 
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x18, // add rsp, 18h
            0x5F,        // pop rdi
            0xC3         // ret 
        };

        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 24; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 14; 
    }
};

template<typename R DECL_TEMPLATE_ARGS(2)>
struct ThunkCodeTemplate<R(DECL_ARGS(2))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(2))>() 
    {
        const static unsigned char thunkCode[] =
        {
            0x40, 0x57, // push rdi
            0x48, 0x8b, 0xfc,  // mov rdi,rsp
            0x48, 0x83, 0xec, 0x20, // sub rsp, 20h 
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x20, // add rsp, 20h
            0x5F,        // pop rdi
            0xC3         // ret 
        };

        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }        
    
    size_t oldAddrOffset() const 
    { 
        return 27; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 17; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(3)>
struct ThunkCodeTemplate<R(DECL_ARGS(3))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(3))>()
    {
        const static unsigned char thunkCode[] =
        {
            0x40, 0x57, // push rdi
            0x48, 0x8b, 0xfc,  // mov rdi,rsp
            0x48, 0x83, 0xec, 0x28, // sub rsp, 28h 
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x28, // add rsp, 28h
            0x5F,        // pop rdi
            0xC3         // ret 
        };

        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 30; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 20; 
    }
};

template<typename R DECL_TEMPLATE_ARGS(4)>
struct ThunkCodeTemplate<R(DECL_ARGS(4))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(4))>()
    {
        const static unsigned char thunkCode[] =
        {
            0x40, 0x57, // push rdi
            0x48, 0x8b, 0xfc,  // mov rdi,rsp
            0x48, 0x83, 0xec, 0x30, // sub rsp, 30h 
            0x4c, 0x89, 0x4c, 0x24, 0x20,  // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x30, // add rsp, 30h
            0x5F,        // pop rdi
            0xC3         // ret 
        };

        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 35; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 25; 
    }
};



template<typename R DECL_TEMPLATE_ARGS(5)>
struct ThunkCodeTemplate<R(DECL_ARGS(5))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(5))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x38, // sub rsp, 38h 
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x38, // add rsp, 38h
            0x5F,        // pop rdi
            0xC3         // ret 
        };

        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 44; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 34; 
    }
};



template<typename R DECL_TEMPLATE_ARGS(6)>
struct ThunkCodeTemplate<R(DECL_ARGS(6))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(6))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x40, // sub rsp, 40h 
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x40, // add rsp, 40h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 53; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 43; 
    }
};



template<typename R DECL_TEMPLATE_ARGS(7)>
struct ThunkCodeTemplate<R(DECL_ARGS(7))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(7))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x48, // sub rsp, 48h 
            0x48, 0x8b, 0x47, 0x40, // mov rax, qword [rdi+40h] 
            0x48, 0x89, 0x44, 0x24, 0x38, // mov qword [rsp+38h],rax
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x48, // add rsp, 48h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 62; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 52; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(8)>
struct ThunkCodeTemplate<R(DECL_ARGS(8))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(8))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x50, // sub rsp, 50h 
            0x48, 0x8b, 0x47, 0x48, // mov rax, qword [rdi+48h] 
            0x48, 0x89, 0x44, 0x24, 0x40, // mov qword [rsp+40h],rax
            0x48, 0x8b, 0x47, 0x40, // mov rax, qword [rdi+40h] 
            0x48, 0x89, 0x44, 0x24, 0x38, // mov qword [rsp+38h],rax
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x50, // add rsp, 50h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 71; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 61; 
    }
};

template<typename R DECL_TEMPLATE_ARGS(9)>
struct ThunkCodeTemplate<R(DECL_ARGS(9))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(9))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x58, // sub rsp, 58h 
            0x48, 0x8b, 0x47, 0x50, // mov rax, qword [rdi+50h] 
            0x48, 0x89, 0x44, 0x24, 0x48, // mov qword [rsp+48h],rax
            0x48, 0x8b, 0x47, 0x48, // mov rax, qword [rdi+48h] 
            0x48, 0x89, 0x44, 0x24, 0x40, // mov qword [rsp+40h],rax
            0x48, 0x8b, 0x47, 0x40, // mov rax, qword [rdi+40h] 
            0x48, 0x89, 0x44, 0x24, 0x38, // mov qword [rsp+38h],rax
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x58, // add rsp, 58h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 80; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 70; 
    }
};

template<typename R DECL_TEMPLATE_ARGS(10)>
struct ThunkCodeTemplate<R(DECL_ARGS(10))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(10))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x60, // sub rsp, 60h 
            0x48, 0x8b, 0x47, 0x58, // mov rax, qword [rdi+58h] 
            0x48, 0x89, 0x44, 0x24, 0x50, // mov qword [rsp+50h],rax
            0x48, 0x8b, 0x47, 0x50, // mov rax, qword [rdi+50h] 
            0x48, 0x89, 0x44, 0x24, 0x48, // mov qword [rsp+48h],rax
            0x48, 0x8b, 0x47, 0x48, // mov rax, qword [rdi+48h] 
            0x48, 0x89, 0x44, 0x24, 0x40, // mov qword [rsp+40h],rax
            0x48, 0x8b, 0x47, 0x40, // mov rax, qword [rdi+40h] 
            0x48, 0x89, 0x44, 0x24, 0x38, // mov qword [rsp+38h],rax
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x60, // add rsp, 60h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 89; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 79; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(11)>
struct ThunkCodeTemplate<R(DECL_ARGS(11))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(11))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x68, // sub rsp, 68h 
            0x48, 0x8b, 0x47, 0x60, // mov rax, qword [rdi+60h] 
            0x48, 0x89, 0x44, 0x24, 0x58, // mov qword [rsp+58h],rax
            0x48, 0x8b, 0x47, 0x58, // mov rax, qword [rdi+58h] 
            0x48, 0x89, 0x44, 0x24, 0x50, // mov qword [rsp+50h],rax
            0x48, 0x8b, 0x47, 0x50, // mov rax, qword [rdi+50h] 
            0x48, 0x89, 0x44, 0x24, 0x48, // mov qword [rsp+48h],rax
            0x48, 0x8b, 0x47, 0x48, // mov rax, qword [rdi+48h] 
            0x48, 0x89, 0x44, 0x24, 0x40, // mov qword [rsp+40h],rax
            0x48, 0x8b, 0x47, 0x40, // mov rax, qword [rdi+40h] 
            0x48, 0x89, 0x44, 0x24, 0x38, // mov qword [rsp+38h],rax
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x68, // add rsp, 68h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);
    }
    
    size_t oldAddrOffset() const 
    { 
        return 98; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 88; 
    }
};


template<typename R DECL_TEMPLATE_ARGS(12)>
struct ThunkCodeTemplate<R(DECL_ARGS(12))> : public ThunkCode 
{ 
    ThunkCodeTemplate<R(DECL_ARGS(12))>()
    {
        const static unsigned char thunkCode[] =
        {            
            0x40, 0x57, // push rdi, rsp changed,  and after call, ret_addr push to stack, rsp changed , so rsp raise 0x10h bytes          
            0x48, 0x8b, 0xfc,  // mov rdi,rsp            
            0x48, 0x83, 0xec, 0x70, // sub rsp, 70h 
            0x48, 0x8b, 0x47, 0x68, // mov rax, qword [rdi+68h] 
            0x48, 0x89, 0x44, 0x24, 0x60, // mov qword [rsp+60h],rax
            0x48, 0x8b, 0x47, 0x60, // mov rax, qword [rdi+60h] 
            0x48, 0x89, 0x44, 0x24, 0x58, // mov qword [rsp+58h],rax
            0x48, 0x8b, 0x47, 0x58, // mov rax, qword [rdi+58h] 
            0x48, 0x89, 0x44, 0x24, 0x50, // mov qword [rsp+50h],rax
            0x48, 0x8b, 0x47, 0x50, // mov rax, qword [rdi+50h] 
            0x48, 0x89, 0x44, 0x24, 0x48, // mov qword [rsp+48h],rax
            0x48, 0x8b, 0x47, 0x48, // mov rax, qword [rdi+48h] 
            0x48, 0x89, 0x44, 0x24, 0x40, // mov qword [rsp+40h],rax
            0x48, 0x8b, 0x47, 0x40, // mov rax, qword [rdi+40h] 
            0x48, 0x89, 0x44, 0x24, 0x38, // mov qword [rsp+38h],rax
            0x48, 0x8b, 0x47, 0x38, // mov rax, qword [rdi+38h] 
            0x48, 0x89, 0x44, 0x24, 0x30, // mov qword [rsp+30h],rax
            0x48, 0x8b, 0x47, 0x30, // mov rax, qword [rdi+30h] 
            0x48, 0x89, 0x44, 0x24, 0x28, // mov qword [rsp+28h],rax
            0x4c, 0x89, 0x4c, 0x24, 0x20, // mov qword [rsp+20h], r9
            0x4d, 0x89, 0xc1,  // mov r9, r8
            0x49, 0x89, 0xd0,  // mov r8, rdx
            0x48, 0x89, 0xca,  // mov rdx, rcx,   param1 is in rcx, move it to rdx, then put old_addr in rcx
            0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
            0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
            0xFF, 0xD0, // call rax
            // return value is returned by rax, so do nothing here but not use rax.
            0x48, 0x83, 0xc4, 0x70, // add rsp, 70h
            0x5F,        // pop rdi
            0xC3         // ret 
        };


        thunkCodeTemplate = thunkCode;
        thunkCodeTemplateSize = sizeof(thunkCode);

        static_assert<sizeof(thunkCode) < MAX_THUNK_CODE_SIZE>();
    }
    
    size_t oldAddrOffset() const 
    { 
        return 107; 
    } 
    
    size_t newAddrOffset() const 
    { 
        return 97; 
    }
};


MOCKCPP_NS_END

#endif

#endif


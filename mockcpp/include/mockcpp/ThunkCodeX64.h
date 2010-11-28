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
    

// return void, parameter number is 0
const unsigned char thunkCodeTemplateV0[]  =  
{ 
    0x40, 0x57, // push rdi
     // sub rsp, 8h          or    fc 8b 48   mov   rdi,rsp ???    how many bytes to reserve? is there return value? what's the type of return value?
    0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
    0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
    0xD0, 0xFF, // call rax
     // add rsp, 8h
    0x5F,       // pop rdi
    0xC3        // ret
};

// return value, parameter number is 0
const unsigned char thunkCodeTemplateR0[]  =  
{ 
    0x40, 0x57, // push rdi
     // sub rsp, 10h          or    fc 8b 48   mov   rdi,rsp ???    how many bytes to reserve? is there return value? what's the type of return value?
    0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax, [new_addr]
    0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx, [old_addr]    -- first parameter to hook
    0xD0, 0xFF, // call rax
     // move return value to the stack caller reserved
     // add rsp, 10h
    0x5F,       // pop rdi
    0xC3        // ret
};



template<typename R DECL_TEMPLATE_ARGS(n)>
struct ThunkCodeTemplate : public ThunkCode
{
    const void *thunkCodeStart() const
    {
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


MOCKCPP_NS_END

#endif

#endif


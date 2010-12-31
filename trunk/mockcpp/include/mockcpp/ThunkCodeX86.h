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

#ifndef __MOCKCPP_THUNK_CODE_X86_H__
#define __MOCKCPP_THUNK_CODE_X86_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ArgumentsMacroHelpers.h>
#include <mockcpp/ThunkCode.h>

MOCKCPP_NS_START


/*   
		|   frame pointer   |<-- ebp
		|   local vars      |
		|   parameters      | para1, para2, ...
		|   ret addr		| call func_to_be_mocked(para1,para2, ...)

					|         func_to_be_mocked: jmp to thunk   
					V
	 |->|   frame pointer   | 
	 |  |   local vars      |
	 |  |   parameters      |   
	 |  |   ret addr        |   
	 |--|   frame pointer   | thunk begin
	    |   old addr        |   
		|   ret addr        | call hook(old_addr, unused, unused, para1, para2, ...)
		| new frame pointer | hook begin
		|-------------------| <- ebp
		|   local vars      |
		|					| 
		|					| 

    
    push ebp
    mov ebp, esp
    mov eax, [new_addr]
    mov ecx, [old_addr]     
    push ecx
    call eax
    leave 
    ret 

    note: leave equals to 
	mov  esp,ebp 
	pop  ebp

	hook function is:
    hook(unsigned int old_addr, void* unused1, void* unused2, ...)
*/


static const unsigned char thunkCodeTemplateX86[]  =  
{ 
    0x55,       // push ebp
    0x8B, 0xEC, // mov ebp, esp
    0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, [new_addr]
    0xB9, 0x00, 0x00, 0x00, 0x00, // mov ecx, [old_addr]
    0x51,       // push ecx
    0xFF, 0xD0, // call eax
    0xC9,       // leave
    0xC3        // ret
};

template<typename F> 
struct ThunkCodeTemplate;

#define THUNK_CODE_TEMPLATE_DEF(n) \
template<typename R DECL_TEMPLATE_ARGS(n)> \
struct ThunkCodeTemplate<R(DECL_ARGS(n))> : public ThunkCode \
{ \
    ThunkCodeTemplate<R(DECL_ARGS(n))>() \
    { \
        thunkCodeTemplate = thunkCodeTemplateX86; \
        thunkCodeTemplateSize = sizeof(thunkCodeTemplateX86); \
    } \
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

THUNK_CODE_TEMPLATE_DEF(0);
THUNK_CODE_TEMPLATE_DEF(1);
THUNK_CODE_TEMPLATE_DEF(2);
THUNK_CODE_TEMPLATE_DEF(3);
THUNK_CODE_TEMPLATE_DEF(4);
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


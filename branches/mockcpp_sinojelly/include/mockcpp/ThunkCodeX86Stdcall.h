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

#ifdef _MSC_VER

#if BUILD_FOR_X86



#ifndef __MOCKCPP_MACHINE_CODE_X86_STDCALL_H__
#define __MOCKCPP_MACHINE_CODE_X86_STDCALL_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ArgumentsMacroHelpers.h>
#include <mockcpp/ThunkCode.h>


MOCKCPP_NS_START



/*   __stdcall

		|   frame pointer   |<-- ebp
		|   local vars      |
		|   parameters      | para1, para2, ...
		|   ret addr		| call func_to_be_mocked(para1,para2, ...)

					|         func_to_be_mocked: jmp to thunk   
					V
	 |->|   frame pointer   | 
	 |  |   local vars      |
	 |  |   parameters      |   
	 |  |   old addr        | thunk begin, pop ret addr, push old addr, push ret addr => make ret addr at stack top  
	 |--|   ret addr        | and then jmp hook(old_addr, para1, para2, ...)
		| new frame pointer | hook begin
		|-------------------| <- ebp
		|   local vars      |
		|					| 
		|					| 

    
    mov eax, [new_addr]
    mov ecx, [old_addr]     
    pop edx   ; pop ret addr
    push ecx
    push edx
    jmp eax

    hook function is:
    hook(unsigned int old_addr, ...)
*/


static const unsigned char thunkCodeTemplateX86Stdcall[]  =  
{ 
    0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, [new_addr]
    0xB9, 0x00, 0x00, 0x00, 0x00, // mov ecx, [old_addr]
    0x5A,           // pop edx
    0x51,           // push ecx
    0x52,           // push edx
    0xFF, 0xE0      // jmp eax
};

#define THUNK_CODE_TEMPLATE_STDCALL_DEF(n) \
template<typename R DECL_TEMPLATE_ARGS(n)> \
struct ThunkCodeTemplate<R __stdcall (DECL_ARGS(n))> : public ThunkCode \
{ \
    ThunkCodeTemplate<R __stdcall (DECL_ARGS(n))>() \
    { \
        thunkCodeTemplate = thunkCodeTemplateX86Stdcall; \
        thunkCodeTemplateSize = sizeof(thunkCodeTemplateX86Stdcall); \
    } \
    size_t oldAddrOffset() const \
    { \
        return 6; \
    } \
    \
    size_t newAddrOffset() const \
    { \
        return 1; \
    } \
}


THUNK_CODE_TEMPLATE_STDCALL_DEF(0);
THUNK_CODE_TEMPLATE_STDCALL_DEF(1);
THUNK_CODE_TEMPLATE_STDCALL_DEF(2);
THUNK_CODE_TEMPLATE_STDCALL_DEF(3);
THUNK_CODE_TEMPLATE_STDCALL_DEF(4);
THUNK_CODE_TEMPLATE_STDCALL_DEF(5);
THUNK_CODE_TEMPLATE_STDCALL_DEF(6);
THUNK_CODE_TEMPLATE_STDCALL_DEF(7);
THUNK_CODE_TEMPLATE_STDCALL_DEF(8);
THUNK_CODE_TEMPLATE_STDCALL_DEF(9);
THUNK_CODE_TEMPLATE_STDCALL_DEF(10);
THUNK_CODE_TEMPLATE_STDCALL_DEF(11);
THUNK_CODE_TEMPLATE_STDCALL_DEF(12);




MOCKCPP_NS_END

#endif

#endif

#endif


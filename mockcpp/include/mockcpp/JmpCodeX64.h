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


#ifndef __MOCKCPP_JMP_CODE_X64_H__
#define __MOCKCPP_JMP_CODE_X64_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ArgumentsMacroHelpers.h>
#include <mockcpp/JmpCode.h>

MOCKCPP_NS_START


// E9 :  jmp near
const unsigned char jmpCodeTemplate[]  =  
{ 
    0xE9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // jmp thunk
};

template <typename F>
struct JmpCodeTemplate;


#define JMP_CODE_TEMPLATE_DEF(n) \
template<typename R DECL_TEMPLATE_ARGS(n)> \
struct JmpCodeTemplate<R(DECL_ARGS(n))> : public JmpCode \
{ \
    const void *jmpCodeStart() const \
    { \
        return jmpCodeTemplate; \
    } \
    \
    size_t jmpCodeLength() const \
    { \
        return sizeof(jmpCodeTemplate); \
    } \
    \
    size_t jmpAddrOffset() const \
    { \
        return 1; \
    } \
}

JMP_CODE_TEMPLATE_DEF(0);
JMP_CODE_TEMPLATE_DEF(1);
JMP_CODE_TEMPLATE_DEF(2);
JMP_CODE_TEMPLATE_DEF(3);
JMP_CODE_TEMPLATE_DEF(4);
JMP_CODE_TEMPLATE_DEF(5);
JMP_CODE_TEMPLATE_DEF(6);
JMP_CODE_TEMPLATE_DEF(7);
JMP_CODE_TEMPLATE_DEF(8);
JMP_CODE_TEMPLATE_DEF(9);
JMP_CODE_TEMPLATE_DEF(10);
JMP_CODE_TEMPLATE_DEF(11);
JMP_CODE_TEMPLATE_DEF(12);





MOCKCPP_NS_END

#endif

#endif


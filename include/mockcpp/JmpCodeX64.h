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

MOCKCPP_NS_START


// FF 25 : JMP /4   jmp absolute indirect
// bytes 2 ~ 5 : operand of jmp, relative to the memory that recorded the thunk addr. it should be zero.
// bytes 6 ~ 13 : the absolute addr of thunk.
static const unsigned char jmpCodeTemplate[]  =  
{     
    0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // jmp thunk
};


static const size_t JMP_CODE_TEMPLATE_SIZE = sizeof(jmpCodeTemplate); 

struct JmpCode
{
    JmpCode(void *from, void *to)
    {    
        code[0] = jmpCodeTemplate[0];
        code[1] = jmpCodeTemplate[1];        
        *(unsigned int *)(code + 2) = 0;  // warning: it must be 4bytes of zero!!
        *(uintptr_t *)(code + 6) = (uintptr_t)to; // warning: can not use long as substitute of __int64, because on windows 64, long is still 32 bits.
    }

    void copy(void *dest)
    {
        memcpy(dest, code, sizeof(code));
    }

private:
    unsigned char code[JMP_CODE_TEMPLATE_SIZE];
};

MOCKCPP_NS_END

#endif

#endif


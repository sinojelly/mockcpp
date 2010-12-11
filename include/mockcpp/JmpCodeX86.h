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

#if BUILD_FOR_X86


#ifndef __MOCKCPP_JMP_CODE_X86_H__
#define __MOCKCPP_JMP_CODE_X86_H__

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START


// E9 :  jmp near
static const unsigned char jmpCodeTemplate[]  =  
{     
    0xE9, 0x00, 0x00, 0x00, 0x00  // jmp thunk
};


static const size_t JMP_CODE_TEMPLATE_SIZE = sizeof(jmpCodeTemplate); 

struct JmpCode
{
    JmpCode(void *from, void *to)
    {    
        code[0] = jmpCodeTemplate[0];
        *(unsigned long*)(code + 1) = 
		    (unsigned long)to - (unsigned long)from - JMP_CODE_TEMPLATE_SIZE;
    }

    void copy(void *dest)
    {
        memcpy(dest, code, sizeof(code));
    }

private:
    char code[JMP_CODE_TEMPLATE_SIZE];
};

MOCKCPP_NS_END

#endif

#endif


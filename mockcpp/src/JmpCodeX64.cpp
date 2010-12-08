/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

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

#include <mockcpp/JmpCodeX64.h>

MOCKCPP_NS_START

struct JmpCodeX64Impl
{
   ////////////////////////////////////////////////
   JmpCodeX64Impl()
   {
      memcpy(m_code, jmpCodeTemplate, sizeof(jmpCodeTemplate));
   }

   ////////////////////////////////////////////////
   void setJmpAddress(void* from, void* to)
   {
        *(uintptr_t *)(code + 6) = (uintptr_t)to; 
   }

   ////////////////////////////////////////////////
   void*  getCodeData() const
   {
      return (void*) m_code;
   }

   ////////////////////////////////////////////////
   size_t getCodeSize() const
   {
      return sizeof(jmpCodeTemplate);
   }

   ////////////////////////////////////////////////

   // FF 25 : JMP /4   jmp absolute indirect
   // bytes 2 ~ 5 : operand of jmp, relative to the memory that recorded the thunk addr. it should be zero.
   // bytes 6 ~ 13 : the absolute addr of thunk.
   static const unsigned char jmpCodeTemplate[]  =
   {
      0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // jmp thunk
   };

   unsigned char m_code[sizeof(jmpCodeTemplate)];
};

///////////////////////////////////////////////////
JmpCodeX64::JmpCodeX64()
   : This(new JmpCodeX64Impl())
{
}

///////////////////////////////////////////////////
JmpCodeX64::~JmpCodeX64()
{
   delete This;
}

///////////////////////////////////////////////////
void
JmpCodeX64::setJmpAddress(void* from, void* to)
{
   This->setJmpAddress(from, to);
}

///////////////////////////////////////////////////
void*
JmpCodeX64::getCodeData() const
{
   return This->getCodeData();
}

///////////////////////////////////////////////////
size_t
JmpCodeX64::getCodeSize() const
{
   return This->getCodeSize();
}

MOCKCPP_NS_END


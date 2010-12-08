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

#include <mockcpp/JmpCodeX86.h>

MOCKCPP_NS_START

struct JmpCodeX86Impl
{
   ////////////////////////////////////////////////
   JmpCodeX86Impl()
   {
      memcpy(m_code, jmpCodeTemplate, sizeof(jmpCodeTemplate));
   }

   ////////////////////////////////////////////////
   void setJmpAddress(void* from, void* to)
   {
        *(unsigned long*)(code + 1) = 
		    (unsigned long)to - (unsigned long)from - sizeof(jmpCodeTemplate);
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
   static const unsigned char jmpCodeTemplate[]  =  
   { 0xE9, 0x00, 0x00, 0x00, 0x00 };

   unsigned char m_code[sizeof(jmpCodeTemplate)];
};

///////////////////////////////////////////////////
JmpCodeX86::JmpCodeX86()
   : This(new JmpCodeX86Impl())
{
}

///////////////////////////////////////////////////
JmpCodeX86::~JmpCodeX86()
{
   delete This;
}

///////////////////////////////////////////////////
void
JmpCodeX86::setJmpAddress(void* from, void* to)
{
   This->setJmpAddress(from, to);
}

///////////////////////////////////////////////////
void*
JmpCodeX86::getCodeData() const
{
   return This->getCodeData();
}

///////////////////////////////////////////////////
size_t
JmpCodeX86::getCodeSize() const
{
   return This->getCodeSize();
}

MOCKCPP_NS_END


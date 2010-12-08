/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2010>  <Darwin Yuan: darwin.yuan@gmail.com>
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

#include <mockcpp/ApiHook.h>
#include <mockcpp/JmpCode.h>
#include <mockcpp/CodeModifier.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////
struct ApiHookImpl
{
   /////////////////////////////////////////////////////
   ApiHookImpl( void* api
              , void* stub
              , CodeModifier* codeModifier)
		: m_jmpCode(api, stub)
        , m_originalData(0)
        , m_api(api)
        , m_codeModifier(codeModifier)
   {
      startHook();
   }

   /////////////////////////////////////////////////////
   ~ApiHookImpl()
   {
      delete m_orignalData;
   }

   /////////////////////////////////////////////////////
   void saveOriginalData()
   {
      m_orignalData = new char[m_jmpCode.getCodeSize()];
      ::memcpy(m_originalData, m_api, m_jmpCode.getCodeSize());
   }

   /////////////////////////////////////////////////////
   void startHook()
   {
      saveOriginalData();
      changeCode(m_jmpCode.getCodeData());
   }

   /////////////////////////////////////////////////////
   void stopHook()
   {
      changeCode(m_originalData);
   }

   /////////////////////////////////////////////////////
   void changeCode(void* data)
   {
      m_codeModifier->modify(m_api, data, m_jmpCode.getCodeSize());
   }

   /////////////////////////////////////////////////////
   JmpCode m_jmpCode;
   char* m_orignalData;
   void* m_api;
   CodeModifier* m_codeModifier;
};

/////////////////////////////////////////////////////////////////
ApiHook::ApiHook 
              ( void* api 
              , void* stub
              , CodeModifier* codeModifier)
	: This(new ApiHookImpl(api, stub, codeModifier))
{
}

/////////////////////////////////////////////////////////////////
ApiHook::~ApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END


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

#ifdef _MSC_VER

#include <windows.h>
#include <mockcpp/CApiHook.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/Win32PageAllocator.h>
#include <mockcpp/Win32ProtectPageAllocator.h>
#include <mockcpp/BlockAllocator.h>

MOCKCPP_NS_START

namespace {

const unsigned char thunkCodeTemplate[]  =  
{ 
  0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, [new_addr]
  0xB9, 0x00, 0x00, 0x00, 0x00, // mov ecx, [old_addr]
  0x5B,       // pop  ebx
  0x51,       // push ecx
  0x53,       // push ebx
  0xFF, 0xD0, // call eax
  0x5B,       // pop  ebx
  0x59,       // pop  ecx
  0x53,       // push ebx
  0xC3        // ret
};

Win32PageAllocator pageAllocator;
Win32ProtectPageAllocator protectPageAllocator(&pageAllocator);
BlockAllocator thunkAllocator(sizeof( thunkCodeTemplate ), &protectPageAllocator);


/////////////////////////////////////////////////////////////////
BOOL modifyCodeSeg(PROC func, char* code, size_t size)
{
    DWORD  dwOldProtect(0);
	DWORD  dwReadWrite(PAGE_EXECUTE_READWRITE);

    BOOL  bRet = TRUE;
	bRet = ::VirtualProtect((LPVOID)func, size, dwReadWrite, &dwOldProtect);
    bRet =  bRet && 
		   ::WriteProcessMemory( ::GetCurrentProcess(),(LPVOID)func, code,  size, NULL );
    bRet =  bRet && 
		   ::VirtualProtect((LPVOID)func, size, dwOldProtect, &dwReadWrite);
    return bRet;
}

}

const unsigned char jmpCodeTemplate[]  =  
{ 
  0xE9, 0x00, 0x00, 0x00, 0x00  // jmp thunk
};

struct CApiHookImpl
{
	CApiHook::Address  m_pfnOld;
	
    char m_byNew[sizeof(jmpCodeTemplate)];  
	char m_byOld[sizeof(jmpCodeTemplate)];

	char *m_thunk;

	BOOL changeCode(char* code);
	bool allocThunk();
	void freeThunk();
	void initHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	void initThunk(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	void startHook();
	void stopHook();
	
	CApiHookImpl(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	~CApiHookImpl();
};

/////////////////////////////////////////////////////////////////
bool CApiHookImpl::allocThunk()
{
	m_thunk = (char *)thunkAllocator.alloc(sizeof( thunkCodeTemplate ));
	return m_thunk != NULL;
}

/////////////////////////////////////////////////////////////////
void CApiHookImpl::freeThunk()
{
	thunkAllocator.free(m_thunk);
}

/////////////////////////////////////////////////////////////////
void CApiHookImpl::initThunk(CApiHook::Address pfnOld, CApiHook::Address pfnNew )
{
	memcpy( m_thunk, thunkCodeTemplate, sizeof( thunkCodeTemplate ) );  
	*(unsigned long*)(m_thunk + 1) = (unsigned long)pfnNew;
	*(unsigned long*)(m_thunk + 6) = (unsigned long)pfnOld;
}

/////////////////////////////////////////////////////////////////
void CApiHookImpl::initHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew )
{
    memcpy( m_byNew, jmpCodeTemplate, sizeof( jmpCodeTemplate ) );  

    *(unsigned long*)(m_byNew + 1) = 
		(unsigned long)m_thunk - (unsigned long)pfnOld - sizeof(jmpCodeTemplate);

    m_pfnOld  =  pfnOld;

    memcpy((void*)m_byOld, (void*)m_pfnOld, sizeof(jmpCodeTemplate));
}

/////////////////////////////////////////////////////////////////
BOOL CApiHookImpl::changeCode(char* code)
{
	return modifyCodeSeg((PROC)m_pfnOld, code,sizeof(jmpCodeTemplate));
}

/////////////////////////////////////////////////////////////////
void CApiHookImpl::startHook()
{
	CApiHookImpl::changeCode((char*)m_byNew);
}

/////////////////////////////////////////////////////////////////
void CApiHookImpl::stopHook()
{
	CApiHookImpl::changeCode((char*)m_byOld);
}

/////////////////////////////////////////////////////////////////
CApiHookImpl::CApiHookImpl(CApiHook::Address pfnOld, CApiHook::Address pfnNew )
{
	if (!allocThunk())
	{
		return;
	}

    initHook(pfnOld, pfnNew);
	initThunk(pfnOld, pfnNew);

	startHook();
}

/////////////////////////////////////////////////////////////////
CApiHookImpl::~CApiHookImpl()
{
	stopHook();
	freeThunk(); // TODO: it must call dtor before destroying the members.
}

/////////////////////////////////////////////////////////////////
CApiHook::CApiHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew)
   : This(new CApiHookImpl(pfnOld, pfnNew))
{
}

/////////////////////////////////////////////////////////////////
CApiHook::~CApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif

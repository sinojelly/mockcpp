
#ifdef _MSC_VER

#include <windows.h>
#include <mockcpp/CApiHook.h>
#include <mockcpp/Asserter.h>

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

/////////////////////////////////////////////////////////////////
BOOL modifyCodeSeg(PROC func, char* code, size_t size)
{
    DWORD  dwOldProtect(0);
	DWORD  dwReadWrite(PAGE_READWRITE);

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
	char m_thunk[sizeof(thunkCodeTemplate)];

	BOOL changeCode(char* code);
	void initHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	void initThunk(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	void startHook();
	void stopHook();
	
	CApiHookImpl(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	~CApiHookImpl();
};

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
    initHook(pfnOld, pfnNew);
	initThunk(pfnOld, pfnNew);

	startHook();
}

/////////////////////////////////////////////////////////////////
CApiHookImpl::~CApiHookImpl()
{
	stopHook();
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

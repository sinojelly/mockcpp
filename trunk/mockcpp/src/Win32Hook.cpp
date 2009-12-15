
#ifdef _MSC_VER

#include <windows.h>
#include <mockcpp/CApiHook.h>

MOCKCPP_NS_START

__declspec( naked ) void mock_wrapper()
{
	__asm {
        pop  ebx // ret address
		push ecx // old address in stack
		push ebx // ret in stack
		call eax // call new address
		pop  ebx // pop ret address
		pop  ecx // pop old function address
		push ebx // push ret to stack
		ret      // return to ret address
	}
}

const unsigned char codeTemplate[]  =  
{ 0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax, [new_addr]
  0xB9, 0x00, 0x00, 0x00, 0x00, // mov ecx, [old_addr]
  0xE9, 0x00, 0x00, 0x00, 0x00  // jmp mock_wrapper
};

struct CApiHookImpl
{
	CApiHook::Address  m_pfnOld;
    char m_byNew[sizeof(codeTemplate)];  
	char m_byOld[sizeof(codeTemplate)];    

	BOOL changeCode(char* code);
	bool initHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	void startHook();
	void stopHook();

	BOOL virtualProtect(DWORD newProtect, PDWORD oldProtect);
	CApiHookImpl(CApiHook::Address pfnOld, CApiHook::Address pfnNew );
	~CApiHookImpl();
};

/////////////////////////////////////////////////////////////////
bool CApiHookImpl::initHook(CApiHook::Address pfnOld, CApiHook::Address pfnNew )
{
    memcpy( m_byNew, codeTemplate, sizeof( codeTemplate ) );  

    *(unsigned long*)(m_byNew + 1)          =  (unsigned long)pfnNew;
	*(unsigned long*)(m_byNew + 5 + 1)      =  (unsigned long)pfnOld;
	*(unsigned long*)(m_byNew + 5 + 5 + 1)  =  \
		(unsigned long)mock_wrapper - \
		(unsigned long)pfnOld - sizeof(codeTemplate);

    m_pfnOld  =  pfnOld;

    memcpy((void*)m_byOld, (void*)m_pfnOld, sizeof(codeTemplate));

	return true;
}

BOOL CApiHookImpl::virtualProtect(DWORD newProtect, PDWORD oldProtect)
{
	return ::VirtualProtect((LPVOID)m_pfnOld,  sizeof(codeTemplate), 
		newProtect, oldProtect);
}
/////////////////////////////////////////////////////////////////
BOOL CApiHookImpl::changeCode(char* code)
{
    DWORD  dwOldProtect(0);
    BOOL  bRet = virtualProtect(PAGE_READWRITE, &dwOldProtect);
    bRet  =  bRet && ::WriteProcessMemory( ::GetCurrentProcess(), 
		(LPVOID)m_pfnOld, code,  sizeof(codeTemplate), NULL );
    bRet  =  bRet && virtualProtect(dwOldProtect, NULL);
    return bRet;
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

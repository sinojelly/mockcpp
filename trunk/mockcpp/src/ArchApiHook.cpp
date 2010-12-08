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

#include <string.h>
#include <inttypes.h>
#include <mockcpp/PageAllocator.h>
#include <mockcpp/BlockAllocator.h>
#include <mockcpp/CodeModifier.h>
#include <mockcpp/ArchApiHook.h>
#include <mockcpp/AllocatorContainer.h>
#include <mockcpp/ThunkCode.h>
#include <mockcpp/JmpCodeX86.h>
#include <mockcpp/JmpCodeX64.h>


MOCKCPP_NS_START


#if 0
namespace {

struct ThunkAllocator 
{
    static void *alloc()
    {
        return allocatorContainer.alloc(maxThunkCodeSize);
    }
    
    static void free(void *p)
    {
        allocatorContainer.free(p);
    }

    static void initialize(PageAllocator *pageAllocator)
    {
        static bool firstRun = true;

        if (firstRun)
        {
            firstRun = false;
            allocatorContainer.initialize(maxThunkCodeSize, pageAllocator);
        }
    }
    
private:
    static AllocatorContainer allocatorContainer;
    static const size_t maxThunkCodeSize = MAX_THUNK_CODE_SIZE;
};

AllocatorContainer ThunkAllocator::allocatorContainer;

}
#endif

/////////////////////////////////////////////////////////////////////////////
struct ArchApiHookImpl
{
	void hook(void* pfnOld, void* pfnNew);

	ArchApiHookImpl(PageAllocator *pageAllocator, CodeModifier *codeModifier);
	~ArchApiHookImpl();

    ////////////////////////////////////////////
	bool changeCode(char* code);
	bool allocThunk();
	void freeThunk();
	void initHook(void* pfnOld, void* pfnNew);
	void initThunk(void* pfnOld, void* pfnNew);
	void startHook();
	void stopHook();

    /////////////////////////////////////////////////
	void* m_pfnOld; // original function address.
	
    char m_byNew[JMP_CODE_TEMPLATE_SIZE];  
	char m_byOld[JMP_CODE_TEMPLATE_SIZE];  

	char *m_thunk; 

    PageAllocator *allocator;
	CodeModifier *modifier;
};

/////////////////////////////////////////////////////////////////
ArchApiHookImpl::ArchApiHookImpl(PageAllocator *pageAllocator, CodeModifier *codeModifier)
	: allocator(pageAllocator), modifier(codeModifier)
{
    ThunkAllocator::initialize(pageAllocator);
}

/////////////////////////////////////////////////////////////////
bool ArchApiHookImpl::allocThunk()
{
	m_thunk = (char *)ThunkAllocator::alloc();
	return m_thunk != 0;
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::freeThunk()
{
	ThunkAllocator::free(m_thunk);
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::initThunk(ApiHook::Address pfnOld, ApiHook::Address pfnNew)
{
	memcpy( m_thunk, thunkTemplate->thunkCodeStart(), thunkTemplate->thunkCodeLength());  
	*(uintptr_t*)(m_thunk + thunkTemplate->newAddrOffset()) = (uintptr_t)pfnNew;
	*(uintptr_t*)(m_thunk + thunkTemplate->oldAddrOffset()) = (uintptr_t)pfnOld;
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::initHook(void* pfnOld, void* pfnNew)
{
    JmpCode jmpCode((void *)pfnOld, (void *)m_thunk);

    jmpCode.copyTo((void *)m_byNew);
    
    m_pfnOld  =  pfnOld;

    memcpy((void*)m_byOld, (void*)m_pfnOld, JMP_CODE_TEMPLATE_SIZE);
}

/////////////////////////////////////////////////////////////////
bool ArchApiHookImpl::changeCode(char* code, size_t size)
{
	return modifier->modify((void *)m_pfnOld, code, size);
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::startHook()
{
	changeCode((char*)m_byNew, sizeof(m_byNew));
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::stopHook()
{
    changeCode((char*)m_byOld, sizeof(m_byOld));
}

/////////////////////////////////////////////////////////////////
void
ArchApiHookImpl::hook
	( void* pfnOld
    , void* pfnNew )
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
ArchApiHookImpl::~ArchApiHookImpl()
{
	stopHook();
	freeThunk(); // TODO: it must call dtor before destroying the members.

	delete allocator;
    delete modifier;
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
ArchApiHook::ArchApiHook
    ( PageAllocator *pageAllocator
    , CodeModifier *codeModifier)
	: This(new ArchApiHookImpl(pageAllocator, codeModifier))
{
}

/////////////////////////////////////////////////////////////////
ArchApiHook::~ArchApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////
void ArchApiHook::hook(void* functionAddress, void* stubAddress)
{
	This->hook(functionAddress, stubAddress);
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END



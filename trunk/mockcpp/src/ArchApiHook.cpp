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
#include <mockcpp/PageAllocator.h>
#include <mockcpp/BlockAllocator.h>
#include <mockcpp/CodeModifier.h>
#include <mockcpp/ArchApiHook.h>
#include <mockcpp/AllocatorContainer.h>
#include <mockcpp/ThunkCode.h>
#include <mockcpp/JmpCode.h>


MOCKCPP_NS_START


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
    static const size_t maxThunkCodeSize = 100;
};

AllocatorContainer ThunkAllocator::allocatorContainer;

}


struct ArchApiHookImpl
{
	void hook(ApiHook::Address pfnOld, ApiHook::Address pfnNew, ThunkCode *thunkTemplate, JmpCode *jmpTemplate);

	ArchApiHookImpl(PageAllocator *pageAllocator, CodeModifier *codeModifier);
	~ArchApiHookImpl();

private:
    static const size_t MAX_JMP_CODE_TEMPLATE_SIZE = 16; 
	ApiHook::Address  m_pfnOld; // save old func addr.
	
    char m_byNew[MAX_JMP_CODE_TEMPLATE_SIZE];  //jmp to thunk
	char m_byOld[MAX_JMP_CODE_TEMPLATE_SIZE];  //save old func content which will be covered with jmp to thunk code, so as to recover it when unhook.
	char *m_thunk; //thunk code, for jumping to mock func(CApiHookFunctor<BOOST_TYPEOF(function)>::hook) and pass old func addr as parameter.

    PageAllocator *allocator;
	CodeModifier *modifier;

    JmpCode *jmpCodeTemplate;

	bool changeCode(char* code, JmpCode *jmpTemplate);
	bool allocThunk();
	void freeThunk();
	void initHook(ApiHook::Address pfnOld, ApiHook::Address pfnNew, JmpCode *jmpTemplate );
	void initThunk(ApiHook::Address pfnOld, ApiHook::Address pfnNew, ThunkCode *thunkTemplate);
	void startHook(JmpCode *jmpTemplate);
	void stopHook();
};

/////////////////////////////////////////////////////////////////
ArchApiHookImpl::ArchApiHookImpl(PageAllocator *pageAllocator, CodeModifier *codeModifier)
	: allocator(pageAllocator), modifier(codeModifier), jmpCodeTemplate(0)
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
void ArchApiHookImpl::initThunk(ApiHook::Address pfnOld, ApiHook::Address pfnNew, ThunkCode *thunkTemplate)
{
	memcpy( m_thunk, thunkTemplate->thunkCodeStart(), thunkTemplate->thunkCodeLength());  
	*(unsigned long*)(m_thunk + thunkTemplate->newAddrOffset()) = (unsigned long)pfnNew;
	*(unsigned long*)(m_thunk + thunkTemplate->oldAddrOffset()) = (unsigned long)pfnOld;
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::initHook(ApiHook::Address pfnOld, ApiHook::Address pfnNew, JmpCode *jmpTemplate)
{
    memcpy( m_byNew, jmpTemplate->jmpCodeStart(), jmpTemplate->jmpCodeLength());  

    *(unsigned long*)(m_byNew + jmpTemplate->jmpAddrOffset()) = 
		(unsigned long)m_thunk - (unsigned long)pfnOld - jmpTemplate->jmpCodeLength();

    m_pfnOld  =  pfnOld;

    memcpy((void*)m_byOld, (void*)m_pfnOld, jmpTemplate->jmpCodeLength());
}

/////////////////////////////////////////////////////////////////
bool ArchApiHookImpl::changeCode(char* code, JmpCode *jmpTemplate)
{
	return modifier->modify((void *)m_pfnOld, code, jmpTemplate->jmpCodeLength());
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::startHook(JmpCode *jmpTemplate)
{
	ArchApiHookImpl::changeCode((char*)m_byNew, jmpTemplate);
    jmpCodeTemplate = jmpTemplate;
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::stopHook()
{
    if (jmpCodeTemplate)
    {
	    ArchApiHookImpl::changeCode((char*)m_byOld, jmpCodeTemplate );
    }
}

/////////////////////////////////////////////////////////////////
void ArchApiHookImpl::hook(ApiHook::Address pfnOld, ApiHook::Address pfnNew, ThunkCode *thunkTemplate, JmpCode *jmpTemplate)
{
	if (!allocThunk())
	{
		return;
	}

    initHook(pfnOld, pfnNew, jmpTemplate);
	initThunk(pfnOld, pfnNew, thunkTemplate);

	startHook(jmpTemplate);
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
ArchApiHook::ArchApiHook(PageAllocator *pageAllocator, CodeModifier *codeModifier)
	: This(new ArchApiHookImpl(pageAllocator, codeModifier))
{
}

/////////////////////////////////////////////////////////////////
ArchApiHook::~ArchApiHook()
{
	delete This;
}

/////////////////////////////////////////////////////////////////
void ArchApiHook::hook(ApiHook::Address pfnOld, ApiHook::Address pfnNew, ThunkCode *thunkTemplate, JmpCode *jmpTemplate)
{
	This->hook(pfnOld, pfnNew, thunkTemplate, jmpTemplate);
}

/////////////////////////////////////////////////////////////////

MOCKCPP_NS_END



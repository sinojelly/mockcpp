
#include <mockcpp/PageAllocator.h>
#include <unistd.h>
#include <sys/mman.h>

MOCKCPP_NS_START

////////////////////////////////////////////////////////////////
namespace
{
    size_t cellingAlign(size_t size)
    {
        return (size + ::getpagesize() - 1)/::getpagesize();
    }
}

////////////////////////////////////////////////////////////////
void* PageAllocator::alloc(size_t size, size_t& actualSize)
{
	actualSize = 0;

    size_t allocatedSize = cellingAlign(size);

    void* addr =  ::mmap((void*)0, allocatedSize, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANON, -1, 0);
    if(addr == MAP_FAILED)
    {
         return 0;
    }

    actualSize = allocatedSize;
    
    return addr;
}

////////////////////////////////////////////////////////////////
void PageAllocator::free(void* p, size_t size)
{
    ::munmap(p, size);
}

////////////////////////////////////////////////////////////////

MOCKCPP_NS_END

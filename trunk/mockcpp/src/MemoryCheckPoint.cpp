
#include <MemoryCheckPoint.h>
#include <Asserter.h>
#include <OutputStringStream.h>

#include <new>
#include <stdlib.h>

MOCKCPP_NS_START

//////////////////////////////////////////////////////////////////
namespace
{
   size_t allocatedSize = 0;
}

//////////////////////////////////////////////////////////////////
MemoryCheckPoint mockcppSetCheckPoint()
{
   return allocatedSize;
}

//////////////////////////////////////////////////////////////////
void mockcppVerifyCheckPoint(MemoryCheckPoint mcp, const char* file, const char* func) throw (Exception)
{
   if(mcp != allocatedSize)
   {
      oss_t oss;
      oss << file << ":" << func << " : memory leak";
      MOCKCPP_FAIL(oss.str());
   }
}

//////////////////////////////////////////////////////////////////
namespace
{
   static const unsigned int magicNumber = 0xFAB587CD;

   struct BlockHeader
   {
      size_t size;
      unsigned int magic;
   };
}

//////////////////////////////////////////////////////////////////
static void* allocateMemory(size_t size) throw (std::bad_alloc)
{

   BlockHeader* header = (BlockHeader*)::malloc(size + sizeof(BlockHeader));
   if(header == 0)
   {
      throw std::bad_alloc();
   }

   header->size = size;
   header->magic = magicNumber;

   allocatedSize += size;
 
   return (void*)((char*)header + sizeof(BlockHeader));
}

//////////////////////////////////////////////////////////////////
static void freeMemory(void* p) throw (Exception)
{
   if(p == 0)
   {
      return;
   }

   BlockHeader* header = (BlockHeader*)((char*)p - sizeof(BlockHeader));

   if(header->magic != magicNumber)
   {
       MOCKCPP_FAIL("Memory Corruption");
   }

   allocatedSize -= header->size;

   ::free(header);
}

MOCKCPP_NS_END

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
USING_MOCKCPP_NS
//////////////////////////////////////////////////////////////////
void* operator new (size_t size) throw (std::bad_alloc)
{
    return allocateMemory(size);
}

//////////////////////////////////////////////////////////////////
void* operator new [] (size_t size) throw (std::bad_alloc)
{
    return allocateMemory(size);
}

//////////////////////////////////////////////////////////////////
void operator delete (void * p)
{
    freeMemory(p);
}

//////////////////////////////////////////////////////////////////
void operator delete [] (void * p)
{
    freeMemory(p);
}
//////////////////////////////////////////////////////////////////

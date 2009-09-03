

// for new/delete
#include <new>
#include <stdlib.h>

// for error string
#include <sstream>

// for opened fd checking
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <testcpp/ResourceCheckPoint.h>

TESTCPP_NS_START

//////////////////////////////////////////////////////////////////
namespace
{
   size_t allocatedSize = 0;
}

unsigned int getNumberOfOpenFiles()
{
    unsigned int maxNumberOfOpenFiles = ::getdtablesize();
    unsigned int openedFiles = 0;
    for(unsigned int fd = 0; fd < maxNumberOfOpenFiles; fd++)
    {
       int flags = 0;
       do{
         flags = ::fcntl(fd, F_GETFD, 0);
       } while(flags == -1 && errno == EINTR);

       if(flags != -1)
       {
         openedFiles++;
       }
    }

    return openedFiles;
}

//////////////////////////////////////////////////////////////////
ResourceCheckPoint testcppSetCheckPoint()
{
   ResourceCheckPoint cp;

   cp.memory = allocatedSize;
   cp.fds = getNumberOfOpenFiles();

   return cp;
}

//////////////////////////////////////////////////////////////////
void testcppVerifyCheckPoint(const ResourceCheckPoint& rcp
      , const char* file, unsigned int line) throw (Error, AssertionFailure)
{
   if(rcp.memory != allocatedSize)
   {
      std::stringstream ss;
      ss << "memory leaked (" << (int)(allocatedSize - rcp.memory) << ") bytes.";
      throw AssertionFailure(file, line, ss.str());
   }

   unsigned int nfds = getNumberOfOpenFiles();
   if(rcp.fds != nfds)
   {
      std::stringstream ss;
      ss << "resource leaking, there are (" 
         << (int)(nfds - rcp.fds) 
         << ") opened file descriptors were not closed.";
      throw AssertionFailure(file, line, ss.str());
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

   struct EndBlock
   {
      unsigned int magic;
   };
}

//////////////////////////////////////////////////////////////////
static void* allocateMemory(size_t size) throw (std::bad_alloc)
{

   BlockHeader* header = (BlockHeader*)::malloc(
               size + sizeof(BlockHeader) + sizeof(EndBlock));
   if(header == 0)
   {
      throw std::bad_alloc();
   }

   header->size = size;
   header->magic = magicNumber;

   allocatedSize += size;

   void * p = (void*)((char*)header + sizeof(BlockHeader));

   EndBlock* endBlock = (EndBlock*)((char*)p + size);
   endBlock->magic = magicNumber;

   printf("allocated %d bytes at %x\n", size, p);

   return p;
}

//////////////////////////////////////////////////////////////////
static void freeMemory(void* p) throw (Error)
{
   if(p == 0)
   {
      return;
   }

   printf("free memory at %x\n", p);

   BlockHeader* header = (BlockHeader*)((char*)p - sizeof(BlockHeader));

   if(header->magic != magicNumber)
   {
      char buf[100];
      snprintf(buf, sizeof(buf), "memory corruption occurred at %x", p);
      throw Error(buf);
   }

   allocatedSize -= header->size;

   EndBlock* endBlock = (EndBlock*)((char*)p + header->size);

   if(endBlock->magic != magicNumber)
   {
      throw Error("Memory Corruption");
   }

   ::free(header);
}

TESTCPP_NS_END

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
USING_TESTCPP_NS

#if 0
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
#endif

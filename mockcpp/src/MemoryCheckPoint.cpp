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

#include <mockcpp/MemoryCheckPoint.h>
#include <mockcpp/Asserter.h>
#include <mockcpp/OutputStringStream.h>

#include <new>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

MOCKCPP_NS_START

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
MemoryCheckPoint mockcppSetCheckPoint()
{
   MemoryCheckPoint cp;

   cp.memory = allocatedSize;
   cp.fds = getNumberOfOpenFiles();

   return cp;
}

//////////////////////////////////////////////////////////////////
void mockcppVerifyCheckPoint(const MemoryCheckPoint& mcp, const char* file, const char* func) throw (Exception)
{
   if(mcp.memory != allocatedSize)
   {
      oss_t oss;
      oss << file << ":" << func << " : memory leak";
      MOCKCPP_FAIL(oss.str());
   }

   if(mcp.fds != getNumberOfOpenFiles())
   {
      oss_t oss;
      oss << file << ":" << func << " : resource leak";
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

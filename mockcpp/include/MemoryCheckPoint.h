
#ifndef __MOCKCPP_MEMORY_CHECK_POINT_H
#define __MOCKCPP_MEMORY_CHECK_POINT_H

#include <mockcpp.h>

#include <Exception.h>

MOCKCPP_NS_START

typedef int MemoryCheckPoint;

MemoryCheckPoint mockcppSetCheckPoint();
void mockcppVerifyCheckPoint(MemoryCheckPoint mcp, \
     const char* file, const char* func) throw (Exception);

#define MOCKCPP_CHECK_POINT_VERIFY(checkpoint) do { \
      mockcppVerifyCheckPoint(checkpoint, __FILE__, __FUNCTION__); \
   } while(0)

MOCKCPP_NS_END

#endif

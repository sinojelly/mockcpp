
#ifndef __TESTNGPPST_SANDBOX_HANDLER_H
#define __TESTNGPPST_SANDBOX_HANDLER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/SandboxTypedef.h>

TESTNGPPST_NS_START

struct SandboxHandler
{
   virtual void handle(ChannelId channelId) = 0;

   virtual ~SandboxHandler() {}
};

TESTNGPPST_NS_END

#endif

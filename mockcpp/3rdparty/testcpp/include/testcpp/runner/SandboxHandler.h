
#ifndef __TESTCPP_SANDBOX_HANDLER_H
#define __TESTCPP_SANDBOX_HANDLER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/SandboxTypedef.h>

TESTCPP_NS_START

struct SandboxHandler
{
   virtual void handle(ChannelId channelId) = 0;

   virtual ~SandboxHandler() {}
};

TESTCPP_NS_END

#endif

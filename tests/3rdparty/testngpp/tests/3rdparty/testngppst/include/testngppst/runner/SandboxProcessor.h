
#ifndef __TESTNGPPST_SANDBOX_PROCESSOR_H
#define __TESTNGPPST_SANDBOX_PROCESSOR_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/SandboxTypedef.h>

TESTNGPPST_NS_START

struct EnvironmentCleaner;
struct SandboxHandler;

struct SandboxProcessor
{
	static void process(ChannelId rChannel, ChannelId wChannel, 
                  EnvironmentCleaner* cleaner, SandboxHandler* handler);
};

TESTNGPPST_NS_END

#endif

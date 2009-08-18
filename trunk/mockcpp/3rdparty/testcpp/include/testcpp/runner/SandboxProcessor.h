
#ifndef __TESTCPP_SANDBOX_PROCESSOR_H
#define __TESTCPP_SANDBOX_PROCESSOR_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/SandboxTypedef.h>

TESTCPP_NS_START

struct EnvironmentCleaner;
struct SandboxHandler;

struct SandboxProcessor
{
	static void process(ChannelId rChannel, ChannelId wChannel, 
                  EnvironmentCleaner* cleaner, SandboxHandler* handler);
};

TESTCPP_NS_END

#endif

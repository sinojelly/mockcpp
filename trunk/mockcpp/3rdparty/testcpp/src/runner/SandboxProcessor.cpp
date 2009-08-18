
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <testcpp/runner/EnvironmentCleaner.h>
#include <testcpp/runner/SandboxHandler.h>
#include <testcpp/runner/SandboxProcessor.h>

TESTCPP_NS_START

void
SandboxProcessor::process(ChannelId rChannel, ChannelId wChannel, \
        EnvironmentCleaner* cleaner, SandboxHandler* childHandler)
{
   cleaner->cleanUp();

   ::close(rChannel);
   int channel = ::dup(wChannel);
   ::close(wChannel);

   childHandler->handle(channel);

   ::close(channel);
}

TESTCPP_NS_END



#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <testngppst/runner/EnvironmentCleaner.h>
#include <testngppst/runner/SandboxHandler.h>
#include <testngppst/runner/SandboxProcessor.h>
#include <testngppst/comm/PipeReadableChannel.h>

TESTNGPPST_NS_START

namespace {
   
   void waitForStartup(int fd)
   {
      PipeReadableChannel channel(fd, false);
      channel.readByte();
   }
}

void
SandboxProcessor::process(ChannelId rChannel, ChannelId wChannel, \
        EnvironmentCleaner* cleaner, SandboxHandler* childHandler)
{
   cleaner->cleanUp();

   ::close(rChannel);
   int channel = ::dup(wChannel);
   ::close(wChannel);

//   waitForStartup(channel);

   childHandler->handle(channel);

   ::close(channel);
}

TESTNGPPST_NS_END


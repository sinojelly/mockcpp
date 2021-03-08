
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#include <testngppst/internal/Error.h>

#include <testngppst/runner/Sandbox.h>
#include <testngppst/runner/EnvironmentCleaner.h>
#include <testngppst/runner/SandboxHandler.h>
#include <testngppst/runner/SandboxProcessor.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////////
struct SandboxImpl
{
   SandboxImpl() : dead(false) {}

   ~SandboxImpl()
   { ::close(channelId); }

   SandboxId getSandboxId() const
   { return sandboxId; }

   ChannelId getChannelId() const
   { return channelId; }
   

   SandboxId sandboxId;
   ChannelId channelId;
   bool dead;
};

////////////////////////////////////////////////////////
Sandbox::Sandbox()
   : This(new SandboxImpl())
{}

////////////////////////////////////////////////////////
Sandbox::~Sandbox()
{
   delete This;
}

////////////////////////////////////////////////////////
ChannelId
Sandbox::getChannelId() const
{
   return This->getChannelId();
}

////////////////////////////////////////////////////////
ChannelId
Sandbox::getSandboxId() const
{
   return This->getSandboxId();
}

////////////////////////////////////////////////////////
void
Sandbox::cleanup()
{
   int stat_loc;

   waitpid(This->sandboxId, &stat_loc, 0);
}

/////////////////////////////////////////////////////////
bool
Sandbox::isDead() const
{
   return This->dead;
}

/////////////////////////////////////////////////////////
void
Sandbox::die()
{
  This->dead = true;
}

////////////////////////////////////////////////////////
Sandbox*
Sandbox::createInstance(EnvironmentCleaner* cleaner, SandboxHandler* childHandler)
{
   int sockets[2];
   int result = ::socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
   if(result < 0)
   {
      throw Error("system error: cannot create channel");
   }

   pid_t pid = ::fork();
   if(pid < 0)
   {
      throw Error("system error: cannot create sandbox");
   }

   if(pid == 0)
   {
      SandboxProcessor::process(sockets[0], sockets[1], cleaner, childHandler);

      exit(0);
   }
   
   ::close(sockets[1]);

   Sandbox * sandbox = new Sandbox();

   sandbox->This->channelId = sockets[0];
   sandbox->This->sandboxId = pid;

   return sandbox;
}

TESTNGPPST_NS_END


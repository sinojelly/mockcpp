
#ifndef __TESTNGPPST_SANDBOX_H
#define __TESTNGPPST_SANDBOX_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/SandboxTypedef.h>

TESTNGPPST_NS_START

struct EnvironmentCleaner;
struct SandboxImpl;
struct SandboxHandler;

struct Sandbox
{
   SandboxId getSandboxId() const;
   ChannelId getChannelId() const;

   bool isDead() const;
   void die();

   void cleanup();

   ~Sandbox();

	static Sandbox*
	createInstance(EnvironmentCleaner* cleaner, SandboxHandler* childHandler);

private:
	Sandbox();

private:
   SandboxImpl* This;
};

TESTNGPPST_NS_END

#endif

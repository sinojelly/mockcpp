
#ifndef __TESTCPP_SANDBOX_H
#define __TESTCPP_SANDBOX_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/SandboxTypedef.h>

TESTCPP_NS_START

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

TESTCPP_NS_END

#endif

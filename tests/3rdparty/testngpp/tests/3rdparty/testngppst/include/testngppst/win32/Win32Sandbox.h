
#ifndef __TESTNGPPST_WIN32_SANDBOX_H
#define __TESTNGPPST_WIN32_SANDBOX_H

#include <windows.h>
#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCase;
struct Win32SandboxImpl;

struct Win32Sandbox
{
   HANDLE getSandboxId() const;
   HANDLE getChannelId() const;
   HANDLE getEventId() const;

   bool isDead() const;
   void die();

   void cleanup();

   ~Win32Sandbox();

	static Win32Sandbox*
	createInstance
	   ( const std::string& suitePath
	   , const TestCase* testcase);

private:
	Win32Sandbox();

private:
   Win32SandboxImpl* This;
};

TESTNGPPST_NS_END

#endif

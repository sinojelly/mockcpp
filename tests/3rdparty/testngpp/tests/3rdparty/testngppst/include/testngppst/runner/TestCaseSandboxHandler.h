
#ifndef __TESTNGPPST_TESTCASE_SANDBOX_HANDLER_H
#define __TESTNGPPST_TESTCASE_SANDBOX_HANDLER_H

#include <testngppst/testngppst.h>

#include <testngppst/runner/SandboxHandler.h>

TESTNGPPST_NS_START

struct TestCase;
struct TestCaseRunner;
struct TestCaseSandboxHandlerImpl;

struct TestCaseSandboxHandler : public SandboxHandler
{
   TestCaseSandboxHandler
         ( const TestCase* testcase
         , TestCaseRunner* runner);

   ~TestCaseSandboxHandler();

   void handle(ChannelId channelId);

private:

   TestCaseSandboxHandlerImpl* This;
};

TESTNGPPST_NS_END

#endif


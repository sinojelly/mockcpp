
#ifndef __TESTCPP_TESTCASE_SANDBOX_HANDLER_H
#define __TESTCPP_TESTCASE_SANDBOX_HANDLER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/SandboxHandler.h>

TESTCPP_NS_START

struct TestCase;
struct TestFixtureDesc;
struct TestCaseRunner;
struct TestCaseSandboxHandlerImpl;

struct TestCaseSandboxHandler : public SandboxHandler
{
   TestCaseSandboxHandler(TestCase* testcase, 
          TestFixtureDesc* fixture, 
          TestCaseRunner* runner);

   ~TestCaseSandboxHandler();

   void handle(ChannelId channelId);

private:

   TestCaseSandboxHandlerImpl* This;
};

TESTCPP_NS_END

#endif


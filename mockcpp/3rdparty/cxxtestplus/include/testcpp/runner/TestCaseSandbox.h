
#ifndef __TESTCPP_TESTCASE_SANDBOX_H
#define __TESTCPP_TESTCASE_SANDBOX_H

#include <testcpp/testcpp.h>

#include <testcpp/Error.h>

#include <testcpp/runner/SandboxTypedef.h>
#include <testcpp/runner/EOFError.h>

TESTCPP_NS_START

struct TestCaseInfoReader;
struct EnvironmentCleaner;
struct TestCase;
struct TestFixtureDesc;
struct TestCaseRunner;
struct TestCaseResultCollector;
struct TestCaseSandboxImpl;

struct TestCaseSandbox
{
   SandboxId getSandboxId() const;
   ChannelId getChannelId() const;

   void handle() throw (Error, EOFError);

   bool isDead() const;

   void cleanup();

   ~TestCaseSandbox();

	static TestCaseSandbox*
	createInstance(EnvironmentCleaner* cleaner, \
          TestCase* testcase, \
          TestFixtureDesc* fixture, \
          TestCaseRunner* runner,
          TestCaseResultCollector* collector);

private:
	TestCaseSandbox();

private:
   TestCaseSandboxImpl* This;
};

TESTCPP_NS_END

#endif

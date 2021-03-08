
#ifndef __TESTNGPPST_TESTCASE_SANDBOX_H
#define __TESTNGPPST_TESTCASE_SANDBOX_H

#include <testngppst/testngppst.h>

#include <testngppst/internal/Error.h>

#include <testngppst/runner/SandboxTypedef.h>
#include <testngppst/runner/EOFError.h>

TESTNGPPST_NS_START

struct TestCaseInfoReader;
struct EnvironmentCleaner;
struct TestCase;
struct TestCaseRunner;
struct TestCaseResultCollector;
struct TestCaseSandboxImpl;

struct TestCaseSandbox
{
   SandboxId getSandboxId() const;
   ChannelId getChannelId() const;

   void handle() TESTNGPPST_THROW(Error, EOFError);
   
   const TestCase* getTestCase() const;

   bool hasSucceeded() const;

   bool isDead() const;

   void cleanup();

   ~TestCaseSandbox();

public:

	static TestCaseSandbox*
	createInstance
         ( EnvironmentCleaner* cleaner
         , const TestCase* testcase
         , TestCaseRunner* runner
         , TestCaseResultCollector* collector
         , bool shouldReport);

private:
	TestCaseSandbox();

private:
   TestCaseSandboxImpl* This;
};

TESTNGPPST_NS_END

#endif

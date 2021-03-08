
#ifndef __TESTNGPPST_TEST_HIERARCHY_SANDBOX_RUNNER_H
#define __TESTNGPPST_TEST_HIERARCHY_SANDBOX_RUNNER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestHierarchyRunner.h>

TESTNGPPST_NS_START

struct TestCaseRunner;
struct TestHierarchySandboxRunnerImpl;

struct TestHierarchySandboxRunner
   : public TestHierarchyRunner
{
   TestHierarchySandboxRunner
         ( unsigned int maxCurrentProcess
         , TestCaseRunner*);

   ~TestHierarchySandboxRunner();

	void run ( TestHierarchyHandler*
            , TestFixtureResultCollector*);

private:
   TestHierarchySandboxRunnerImpl* This;
};

TESTNGPPST_NS_END

#endif


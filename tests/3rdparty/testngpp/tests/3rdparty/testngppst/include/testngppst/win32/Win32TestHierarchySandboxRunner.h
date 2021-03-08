
#ifndef __TESTNGPPST_WIN32_TEST_HIERARCHY_SANDBOX_RUNNER_H
#define __TESTNGPPST_WIN32_TEST_HIERARCHY_SANDBOX_RUNNER_H

#include <string>

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestHierarchyRunner.h>

TESTNGPPST_NS_START

struct TestCaseRunner;
struct Win32TestHierarchySandboxRunnerImpl;

struct Win32TestHierarchySandboxRunner
   : public TestHierarchyRunner
{
   Win32TestHierarchySandboxRunner
         ( unsigned int maxCurrentProcess
         , TestCaseRunner*);

   ~Win32TestHierarchySandboxRunner();

	void run ( TestHierarchyHandler*
            , TestFixtureResultCollector*);

private:
   Win32TestHierarchySandboxRunnerImpl* This;
};

TESTNGPPST_NS_END

#endif


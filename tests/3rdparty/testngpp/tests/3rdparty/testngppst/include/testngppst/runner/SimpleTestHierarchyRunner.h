
#ifndef __TESTNGPPST_SIMPLE_TEST_HIERARCHY_RUNNER_H
#define __TESTNGPPST_SIMPLE_TEST_HIERARCHY_RUNNER_H

#include <testngppst/runner/TestHierarchyRunner.h>

TESTNGPPST_NS_START

///////////////////////////////////////////////////////

struct TestHierarchyHandler;
struct TestFixtureResultCollector;
struct TestCaseRunner;

struct SimpleTestHierarchyRunnerImpl;

struct SimpleTestHierarchyRunner : public TestHierarchyRunner
{
	SimpleTestHierarchyRunner(TestCaseRunner* runner);
	~SimpleTestHierarchyRunner();

	void run( TestHierarchyHandler* 
           , TestFixtureResultCollector*);

private:
   SimpleTestHierarchyRunnerImpl * This;
};

///////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif


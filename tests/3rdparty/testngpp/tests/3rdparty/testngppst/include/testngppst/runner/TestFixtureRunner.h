
#ifndef __TESTNGPPST_TEST_FIXTURE_RUNNER_H__
#define __TESTNGPPST_TEST_FIXTURE_RUNNER_H__

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestFixtureContext;
struct TestFixtureResultCollector;
struct TestHierarchyRunner;
struct TestCaseFilter;
struct TestFixtureRunnerImpl;

struct TestFixtureRunner
{
   TestFixtureRunner(TestHierarchyRunner* runner);
   ~TestFixtureRunner();

   void run ( TestFixtureContext *
            , TestFixtureResultCollector*
            , const TestCaseFilter*
			, const std::string&);

private:
   TestFixtureRunnerImpl* This;
};

TESTNGPPST_NS_END

#endif


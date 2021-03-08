
#ifndef __TESTNGPPST_TEST_SUITE_RUNNER_H
#define __TESTNGPPST_TEST_SUITE_RUNNER_H

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestSuiteContext;
struct TestCaseFilter;
struct TestFixtureRunner;
struct TestResultCollector;

struct TestSuiteRunnerImpl;

struct TestSuiteRunner
{
	TestSuiteRunner( TestFixtureRunner*
                  , TestResultCollector* );
	~TestSuiteRunner();

   void run(TestSuiteContext* suite
            , const TestCaseFilter* filter);
private:
	TestSuiteRunnerImpl* This;

};

TESTNGPPST_NS_END

#endif



#ifndef __TESTCPP_SIMPLE_TEST_FIXTURE_RUNNER_H
#define __TESTCPP_SIMPLE_TEST_FIXTURE_RUNNER_H

#include <testcpp/runner/TestFixtureRunner.h>

TESTCPP_NS_START

///////////////////////////////////////////////////////
struct SimpleTestFixtureRunnerImpl;
struct TestFixtureDesc;
struct TestFixtureResultCollector;
struct TestCaseFilter;
struct TestCaseRunner;

struct SimpleTestFixtureRunner : public TestFixtureRunner
{
	SimpleTestFixtureRunner(TestCaseRunner* runner);
	~SimpleTestFixtureRunner();

	void run(TestFixtureDesc* fixture
      , TestFixtureResultCollector* resultCollector
      , const TestCaseFilter* filter);

private:
	SimpleTestFixtureRunnerImpl * This;
};

///////////////////////////////////////////////////////

TESTCPP_NS_END

#endif


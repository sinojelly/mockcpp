
#ifndef __TESTCPP_TEST_FIXTURE_RUNNER_WRAPPER_H
#define __TESTCPP_TEST_FIXTURE_RUNNER_WRAPPER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFixtureRunner.h>

TESTCPP_NS_START

struct TestFixtureDesc;
struct TestFixtureResultCollector;

struct TestFixtureRunnerWrapper
	: public TestFixtureRunner
{
   TestFixtureRunnerWrapper(TestFixtureRunner* runner);
   ~TestFixtureRunnerWrapper();

	void run ( TestFixtureDesc*
            , TestFixtureResultCollector*
            , const TestCaseFilter*);

private:
   TestFixtureRunner* fixtureRunner;
};

TESTCPP_NS_END

#endif


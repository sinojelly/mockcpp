
#ifndef __TESTNGPP_SIMPLE_TEST_CASE_RUNNER_H
#define __TESTNGPP_SIMPLE_TEST_CASE_RUNNER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestCaseRunner.h>
#include <testngpp/runner/TestCaseRunnerDieHandler.h>

TESTNGPP_NS_START

struct SimpleTestCaseRunner
	: public TestCaseRunner
{
	SimpleTestCaseRunner(TestCaseRunnerDieHandler* dieHandler)
		: handler(dieHandler)
	{}

	~SimpleTestCaseRunner()
	{
		if(handler != 0)
		{
			delete handler;
		}
	}

	bool run(TestCase*, TestCaseResultCollector*, bool reportSuccess=true);

private:
    TestCaseRunnerDieHandler* handler;
};

TESTNGPP_NS_END

#endif



#ifndef __TESTCPP_SIMPLE_TEST_CASE_RUNNER_H
#define __TESTCPP_SIMPLE_TEST_CASE_RUNNER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestCaseRunner.h>

TESTCPP_NS_START

struct SimpleTestCaseRunner
	: public TestCaseRunner
{
	void run(TestFixtureDesc*, TestCase*, TestCaseResultCollector*);
};

TESTCPP_NS_END

#endif


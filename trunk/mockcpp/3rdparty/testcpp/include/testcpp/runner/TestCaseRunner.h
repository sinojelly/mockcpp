
#ifndef __TESTCPP_TEST_CASE_RUNNER_H
#define __TESTCPP_TEST_CASE_RUNNER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixtureDesc;
struct TestCase;
struct TestCaseResultCollector;

struct TestCaseRunner
{
	virtual void run(TestFixtureDesc*, TestCase*, TestCaseResultCollector*) = 0;

   virtual ~TestCaseRunner() {}
};

TESTCPP_NS_END

#endif


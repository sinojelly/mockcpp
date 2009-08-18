
#ifndef __TESTCPP_TEST_FIXTURE_RUNNER_H
#define __TESTCPP_TEST_FIXTURE_RUNNER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixtureDesc;
struct TestFixtureResultCollector;

struct TestFixtureRunner
{
	virtual void run (TestFixtureDesc*, TestFixtureResultCollector*) = 0;
};

TESTCPP_NS_END

#endif


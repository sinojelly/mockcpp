
#ifndef __TESTNGPPST_SIMPLE_TEST_CASE_RUNNER_H
#define __TESTNGPPST_SIMPLE_TEST_CASE_RUNNER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/TestCaseRunner.h>

TESTNGPPST_NS_START

struct SimpleTestCaseRunner
	: public TestCaseRunner
{
	bool run(TestCase*, TestCaseResultCollector*, bool reportSuccess=true);
};

TESTNGPPST_NS_END

#endif



#ifndef __TESTNGPP_TESTCASE_RUNNER_DIE_HANDLER_H
#define __TESTNGPP_TESTCASE_RUNNER_DIE_HANDLER_H

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct TestCase;
struct TestCaseResultCollector;

struct TestCaseRunnerDieHandler
{
	void die(TestCase*, TestCaseResultCollector*);
};

TESTNGPP_NS_END

#endif


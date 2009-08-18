
#ifndef __TESTCPP_TEST_SUITE_RUNNER_H
#define __TESTCPP_TEST_SUITE_RUNNER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestSuiteLoader;
struct TestFixtureRunner;
struct TestSuiteResultCollector;
struct TestSuiteRunnerImpl;

struct TestSuiteRunner
{
	TestSuiteRunner(TestSuiteLoader*, TestFixtureRunner* );
	~TestSuiteRunner();

	void run(const std::string& path, TestSuiteResultCollector*);

private:
	TestSuiteRunnerImpl* This;

};

TESTCPP_NS_END

#endif


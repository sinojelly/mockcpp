
#ifndef __TESTCPP_TEST_SUITE_RESULT_COLLECTOR_H
#define __TESTCPP_TEST_SUITE_RESULT_COLLECTOR_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestFixtureResultCollector.h>

TESTCPP_NS_START

struct TestSuiteInfoReader;

struct TestSuiteResultCollector
	: public TestFixtureResultCollector
{
   virtual void startTestSuite(TestSuiteInfoReader*) = 0;
   virtual void endTestSuite(TestSuiteInfoReader*) = 0;
   virtual void addSuiteError(TestSuiteInfoReader*, const std::string&) = 0;

	virtual ~TestSuiteResultCollector() {}
};

TESTCPP_NS_END

#endif


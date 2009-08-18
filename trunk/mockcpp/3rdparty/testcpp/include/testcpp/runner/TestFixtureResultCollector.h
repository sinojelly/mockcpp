
#ifndef __TESTCPP_TEST_FIXTURE_RESULT_COLLECTOR_H
#define __TESTCPP_TEST_FIXTURE_RESULT_COLLECTOR_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestCaseResultCollector.h>

TESTCPP_NS_START

struct TestFixtureInfoReader;

struct TestFixtureResultCollector
	: public TestCaseResultCollector
{
   virtual void startTestFixture(TestFixtureInfoReader*) = 0;
   virtual void endTestFixture(TestFixtureInfoReader*) = 0;

   virtual void addFixtureError(TestFixtureInfoReader*, const std::string&) = 0;
	virtual void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&) = 0;

	virtual ~TestFixtureResultCollector() {}
};

TESTCPP_NS_END

#endif


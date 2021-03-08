
#ifndef __TESTNGPPST_TEST_FIXTURE_RESULT_COLLECTOR_H
#define __TESTNGPPST_TEST_FIXTURE_RESULT_COLLECTOR_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestCaseResultCollector.h>

TESTNGPPST_NS_START

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

TESTNGPPST_NS_END

#endif


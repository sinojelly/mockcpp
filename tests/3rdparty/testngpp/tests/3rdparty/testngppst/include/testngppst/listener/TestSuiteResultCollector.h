
#ifndef __TESTNGPPST_TEST_SUITE_RESULT_COLLECTOR_H
#define __TESTNGPPST_TEST_SUITE_RESULT_COLLECTOR_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestFixtureResultCollector.h>

TESTNGPPST_NS_START

struct TestSuiteInfoReader;

struct TestSuiteResultCollector
	: public TestFixtureResultCollector
{
   virtual void startTestSuite(TestSuiteInfoReader*) = 0;
   virtual void endTestSuite(TestSuiteInfoReader*) = 0;
   virtual void addSuiteError(TestSuiteInfoReader*, const std::string&) = 0;

	virtual ~TestSuiteResultCollector() {}
};

TESTNGPPST_NS_END

#endif


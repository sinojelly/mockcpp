
#ifndef __TESTCPP_TEST_RESULT_COLLECTOR_H
#define __TESTCPP_TEST_RESULT_COLLECTOR_H

#include <string>

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestSuiteResultCollector.h>

TESTCPP_NS_START

struct TestResultCollector
   : public TestSuiteResultCollector
{
   virtual void startTest() = 0;
   virtual void endTest() = 0;

   virtual void addError(const std::string&) = 0;

	virtual ~TestResultCollector() {}
};

TESTCPP_NS_END

#endif


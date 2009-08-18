
#ifndef __TESTCPP_TEST_CASE_RESULT_COLLECTOR_H
#define __TESTCPP_TEST_CASE_RESULT_COLLECTOR_H

#include <string>

#include <testcpp/testcpp.h>
#include <testcpp/AssertionFailure.h>

TESTCPP_NS_START

struct AssertionFailure;
struct TestCaseInfoReader;

struct TestCaseResultCollector
{
   virtual void addCaseCrash(TestCaseInfoReader*) = 0;
	virtual void addCaseError(TestCaseInfoReader*, const std::string&) = 0;
	virtual void addCaseFailure(TestCaseInfoReader*, const AssertionFailure&)  = 0;

   virtual void startTestCase(TestCaseInfoReader*) = 0;
   virtual void endTestCase(TestCaseInfoReader*) = 0;

	virtual ~TestCaseResultCollector() {}
};

TESTCPP_NS_END

#endif


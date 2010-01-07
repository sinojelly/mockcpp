
#ifndef __TESTCPP_SIMPLE_TEST_CASE_RESULT_REPORTER_H
#define __TESTCPP_SIMPLE_TEST_CASE_RESULT_REPORTER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestCaseListener.h>
#include <testcpp/runner/TestCaseResultReporter.h>

TESTCPP_NS_START

struct SimpleTestCaseResultReporterImpl;

struct SimpleTestCaseResultReporter
   : public TestCaseResultReporter
   , public TestCaseListener
{
	SimpleTestCaseResultReporter();
	~SimpleTestCaseResultReporter();

   unsigned int getTestCaseResult(TestCaseInfoReader*) const;

   void addCaseError(TestCaseInfoReader*, const std::string&);
   void addCaseCrash(TestCaseInfoReader*);
   void addCaseFailure(TestCaseInfoReader*, const AssertionFailure&);
   void startTestCase(TestCaseInfoReader*);
   void endTestCase(TestCaseInfoReader*);

private:
   SimpleTestCaseResultReporterImpl * This;
};

TESTCPP_NS_END

#endif


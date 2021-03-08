
#ifndef __TESTNGPPST_SIMPLE_TEST_CASE_RESULT_REPORTER_H
#define __TESTNGPPST_SIMPLE_TEST_CASE_RESULT_REPORTER_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestCaseListener.h>
#include <testngppst/listener/TestCaseResultReporter.h>

TESTNGPPST_NS_START

struct SimpleTestCaseResultReporterImpl;

struct SimpleTestCaseResultReporter
   : public TestCaseResultReporter
   , public TestCaseListener
{
	SimpleTestCaseResultReporter();
	~SimpleTestCaseResultReporter();

   unsigned int getTestCaseResult(const TestCaseInfoReader*) const;

   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

private:
   SimpleTestCaseResultReporterImpl * This;
};

TESTNGPPST_NS_END

#endif


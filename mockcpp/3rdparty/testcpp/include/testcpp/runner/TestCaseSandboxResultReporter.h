
#ifndef __TESTCPP_TESTCASE_SANDBOX_RESULT_REPORTER_H
#define __TESTCPP_TESTCASE_SANDBOX_RESULT_REPORTER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestCaseResultCollector.h>

TESTCPP_NS_START

struct TestCaseSandboxResultReporterImpl;
struct WrittableChannel;

struct TestCaseSandboxResultReporter
   : public TestCaseResultCollector
{
   TestCaseSandboxResultReporter(WrittableChannel* channel);
   ~TestCaseSandboxResultReporter();

   void addCaseCrash(TestCaseInfoReader*) {}
   void addCaseError(TestCaseInfoReader*, const std::string&); 
   void addCaseFailure(TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(TestCaseInfoReader*); 
   void endTestCase(TestCaseInfoReader*);

private:
   TestCaseSandboxResultReporterImpl* This;
};

TESTCPP_NS_END

#endif


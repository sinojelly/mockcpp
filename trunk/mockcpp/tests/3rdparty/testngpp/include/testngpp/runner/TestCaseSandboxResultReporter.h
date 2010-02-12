
#ifndef __TESTNGPP_TESTCASE_SANDBOX_RESULT_REPORTER_H
#define __TESTNGPP_TESTCASE_SANDBOX_RESULT_REPORTER_H

#include <testngpp/testngpp.h>
#include <testngpp/runner/TestCaseResultCollector.h>

TESTNGPP_NS_START

struct TestCaseSandboxResultReporterImpl;
struct WrittableChannel;

struct TestCaseSandboxResultReporter
   : public TestCaseResultCollector
{
   TestCaseSandboxResultReporter(WrittableChannel* channel);
   ~TestCaseSandboxResultReporter();

   void addCaseCrash(const TestCaseInfoReader*) {}
   void addCaseSkipped(const TestCaseInfoReader*) {}
   void addCaseError(const TestCaseInfoReader*, const std::string&); 
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*); 
   void endTestCase(const TestCaseInfoReader*);

private:
   TestCaseSandboxResultReporterImpl* This;
};

TESTNGPP_NS_END

#endif


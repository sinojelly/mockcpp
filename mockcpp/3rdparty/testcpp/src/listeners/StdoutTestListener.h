
#ifndef __TESTCPP_STDOUT_TEST_LISTENER_H
#define __TESTCPP_STDOUT_TEST_LISTENER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestListener.h>

TESTCPP_NS_START

struct TestSuiteInfoReader;
struct TestResultReporter;
struct TestCaseResultReporter;
struct StdoutTestListenerImpl;

struct StdoutTestListener
   : public TestListener
{
   StdoutTestListener(TestResultReporter*, TestCaseResultReporter* caseReporter);
   ~StdoutTestListener();

   void addCaseCrash(TestCaseInfoReader*);
   void addCaseError(TestCaseInfoReader*, const std::string&);
   void addCaseFailure(TestCaseInfoReader*, const AssertionFailure&);
   void startTestCase(TestCaseInfoReader*);
   void endTestCase(TestCaseInfoReader*);

   void startTestFixture(TestFixtureInfoReader*);
   void endTestFixture(TestFixtureInfoReader*);
   void addFixtureError(TestFixtureInfoReader*, const std::string&);
   void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&);

   void startTestSuite(TestSuiteInfoReader*);
   void endTestSuite(TestSuiteInfoReader*);
   void addSuiteError(TestSuiteInfoReader*, const std::string&);
   void addError(const std::string&);

private:

   StdoutTestListenerImpl* This;
};

TESTCPP_NS_END

#endif



#ifndef __TESTCPP_COLORFUL_STDOUT_TEST_LISTENER_H
#define __TESTCPP_COLORFUL_STDOUT_TEST_LISTENER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestListener.h>

TESTCPP_NS_START

struct TestSuiteInfoReader;
struct TestResultReporter;
struct TestSuiteResultReporter;
struct TestCaseResultReporter;
struct ColorfulStdoutTestListenerImpl;

struct ColorfulStdoutTestListener
   : public TestListener
{
   ColorfulStdoutTestListener( TestResultReporter*
                     , TestSuiteResultReporter*
                     , TestCaseResultReporter* );
   ~ColorfulStdoutTestListener();

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

   void startTest();
   void endTest();
   void addError(const std::string&);

private:

   ColorfulStdoutTestListenerImpl* This;
};

TESTCPP_NS_END

#endif


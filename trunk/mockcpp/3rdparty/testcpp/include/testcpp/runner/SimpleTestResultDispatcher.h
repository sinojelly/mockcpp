
#ifndef __TESTCPP_SIMPLE_TEST_RESULT_DISPATCHER_H
#define __TESTCPP_SIMPLE_TEST_RESULT_DISPATCHER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestSuiteResultCollector.h>
#include <testcpp/runner/TestResultDispatcher.h>
#include <testcpp/runner/TestCaseResultDispatcher.h>
#include <testcpp/runner/TestResultReporter.h>

TESTCPP_NS_START

struct TestSuiteInfoReader;
struct SimpleTestResultDispatcherImpl;

struct SimpleTestResultDispatcher
   : public TestResultDispatcher
   , public TestCaseResultDispatcher
   , public TestSuiteResultCollector
{
   SimpleTestResultDispatcher();
   ~SimpleTestResultDispatcher();

   void registerListener(TestListener* listner);

   void registerTestCaseListener(TestCaseListener* listener);
   TestCaseListener* unregisterTestCaseListener(TestCaseListener* listener);

   void addCaseError(TestCaseInfoReader*, const std::string&);
   void addCaseCrash(TestCaseInfoReader*);
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
   SimpleTestResultDispatcherImpl *This;
};

TESTCPP_NS_END

#endif


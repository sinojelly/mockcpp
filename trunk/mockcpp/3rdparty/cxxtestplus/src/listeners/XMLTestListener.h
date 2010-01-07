
#ifndef __TESTCPP_XML_TEST_LISTENER_H
#define __TESTCPP_XML_TEST_LISTENER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestListener.h>
#include <sstream>

TESTCPP_NS_START

struct TestSuiteInfoReader;
struct TestResultReporter;
struct TestSuiteResultReporter;
struct TestCaseResultReporter;
struct XMLTestListenerImpl;

struct XMLTestListener
   : public TestListener
{
   XMLTestListener( TestResultReporter*
                     , TestSuiteResultReporter*
                     , TestCaseResultReporter*
                     , std::ostream& os);
   ~XMLTestListener();

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

	XMLTestListenerImpl* This;
};

TESTCPP_NS_END

#endif

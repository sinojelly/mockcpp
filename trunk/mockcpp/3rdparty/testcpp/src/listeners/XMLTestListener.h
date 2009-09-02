
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

// TODO: use const wherever possible

struct XMLTestListener
   : public TestListener
{
   XMLTestListener( TestResultReporter*
                     , TestSuiteResultReporter*
                     , TestCaseResultReporter* );
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
	TestResultReporter* testResultReporter;
	TestSuiteResultReporter* testSuiteResultReporter;
	TestCaseResultReporter* testCaseResultReporter;

	std::ostream& os;
	std::ostringstream testcaseBuffer;

	std::string intToString(int i) const;
	const std::string formatMessage(const std::string type, const std::string message);
	void writeTestCase(const TestCaseInfoReader* testcase, const std::string& message);
};

TESTCPP_NS_END

#endif

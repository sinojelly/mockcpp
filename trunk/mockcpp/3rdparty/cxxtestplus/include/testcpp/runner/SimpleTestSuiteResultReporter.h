
#ifndef __TESTCPP_SIMPLE_TEST_SUITE_RESULT_REPORTER_H
#define __TESTCPP_SIMPLE_TEST_SUITE_RESULT_REPORTER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/TestSuiteListener.h>
#include <testcpp/runner/TestSuiteResultReporter.h>

TESTCPP_NS_START

struct TestCaseResultReporter;
struct SimpleTestSuiteResultReporterImpl;

struct SimpleTestSuiteResultReporter
   : public TestSuiteResultReporter
   , public TestSuiteListener
{
	SimpleTestSuiteResultReporter(TestCaseResultReporter*);
	~SimpleTestSuiteResultReporter();

   ////////////////////////////////////////////////////////////
   int getNumberOfTestCases(TestSuiteInfoReader*) const;
   int getNumberOfSuccessfulTestCases(TestSuiteInfoReader*) const;
   int getNumberOfUnsuccessfulTestCases(TestSuiteInfoReader*) const;
   int getNumberOfFailedTestCases(TestSuiteInfoReader*) const;
   int getNumberOfErrorTestCases(TestSuiteInfoReader*) const;
   int getNumberOfCrashedTestCases(TestSuiteInfoReader*) const;
   int getNumberOfFixtureErrors(TestSuiteInfoReader*) const;
   int getNumberOfFixtureFailures(TestSuiteInfoReader*) const;
   int getNumberOfSuiteErrors(TestSuiteInfoReader*) const;

   ////////////////////////////////////////////////////////////
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

private:
   SimpleTestSuiteResultReporterImpl* This;

};

TESTCPP_NS_END

#endif


#include "XMLTestListener.h"

#include <iostream>
#include <ctime>

/*
 ## doc type definition (in relaxng compact syntax)

 start = testsuites

 testsuites = element testsuites {
 testsuite*
 }

 testsuite = element testsuite {
 attribute name { text },
 attribute tests { xsd:integer },
 attribute fixtures { xsd:integer },
 attribute crashes { xsd:integer },
 attribute errors { xsd:integer },
 attribute failures { xsd:integer },
 element testcase*
 }

 testcase = element testcase {
 attribute name { text },
 attribute fixture { text },
 attribute time { xsd:float },
 attribute filename { text },
 (element crash { text }
 | element error { text }
 | element failure { text })?
 }

 */

#include <testcpp/Error.h>
#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestSuiteInfoReader.h>
#include <testcpp/internal/TestFixtureInfoReader.h>

#include <testcpp/runner/TestResultReporter.h>
#include <testcpp/runner/TestSuiteResultReporter.h>
#include <testcpp/runner/TestCaseResultReporter.h>
#include <testcpp/runner/InternalError.h>

TESTCPP_NS_START

XMLTestListener::XMLTestListener(TestResultReporter* testResultReporter
		, TestSuiteResultReporter* testSuiteResultReporter
		, TestCaseResultReporter* testCaseResultReporter)
: testResultReporter(testResultReporter)
, testSuiteResultReporter(testSuiteResultReporter)
, testCaseResultReporter(testCaseResultReporter)
, os(std::cout)
{
}

XMLTestListener::~XMLTestListener()
{
}

void XMLTestListener::
addCaseCrash(TestCaseInfoReader* testcase)
{
	writeTestCase(testcase, formatMessage("crash", "test case crashed unexpectedly."));
}

void XMLTestListener::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
	writeTestCase(testcase, formatMessage("error", msg));
}

void XMLTestListener::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
	writeTestCase(testcase, formatMessage("failure", failure.what()));
}

const std::string XMLTestListener::formatMessage(const std::string type, const std::string message) {
	std::stringstream stream;
	stream << "      <"
		<< type
		<< ">"
		<< message
		<< "       </"
		<< type
		<< ">"
		<< std::endl;
	return stream.str();
}

void XMLTestListener::
writeTestCase(const TestCaseInfoReader* testcase, const std::string& message) {
	testcaseBuffer << "    <testcase"
	<< " name=\"" << testcase->getName() << "\""
	<< " fixture=\"" << testcase->getNameOfFixture() << "\""
	<< " time=\"" << "0" << "\""
	<< " filename=\"" << testcase->getFileName() << "\""
	<< ">" << std::endl;

	testcaseBuffer << message;

	testcaseBuffer << "    </testcase>" << std::endl;
}

void XMLTestListener::
startTestCase(TestCaseInfoReader* testcase)
{
}

void XMLTestListener::
endTestCase(TestCaseInfoReader* testcase)
{
	switch(testCaseResultReporter->getTestCaseResult(testcase))
	{
	case TestCaseResultReporter::CRASHED:
	case TestCaseResultReporter::FAILED:
	case TestCaseResultReporter::ERROR:
		return;
	}

	writeTestCase(testcase, "");
}

void XMLTestListener::
startTestFixture(TestFixtureInfoReader* fixtureinfo)
{
}

void XMLTestListener::
endTestFixture(TestFixtureInfoReader*)
{
}

void XMLTestListener::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
}

void XMLTestListener::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure& failure)
{
}

void XMLTestListener::
startTestSuite(TestSuiteInfoReader* suite)
{
	os << "  <testsuite";
	os.flush();
	testcaseBuffer.str("");
}

void XMLTestListener::
endTestSuite(TestSuiteInfoReader* suite)
{
	os << " tests=\"" << intToString(suite->getNumberOfTestCases()) << "\""
	<< " fixtures=\"" << intToString(suite->getNumberOfTestFixtures()) << "\""
	<< " crashes=\"" << intToString(testSuiteResultReporter->getNumberOfCrashedTestCases(suite)) << "\""
	<< " errors=\"" << intToString(testSuiteResultReporter->getNumberOfErrorTestCases(suite)) << "\""
	<< " failures=\"" << intToString(testSuiteResultReporter->getNumberOfFailedTestCases(suite)) << "\""
	<< ">" << std::endl;

	os << testcaseBuffer.str();

	os << "  </testsuite>" << std::endl;
}

void XMLTestListener::
addSuiteError(TestSuiteInfoReader*, const std::string& msg)
{
}

void XMLTestListener::startTest()
{
	os << "<?xml version=\"1.0\"?>"
	<< std::endl
	<< "<testsuites>"
	<< std::endl;
}

void XMLTestListener::endTest()
{
	os << "</testsuites>"
		<< std::endl;
}

void XMLTestListener::
addError(const std::string& msg)
{
}

std::string XMLTestListener::intToString(int i) const
{
	std::ostringstream stream;
	stream << i;
	return stream.str();
}

TESTCPP_NS_END

///////////////////////////////////////////////////////////
USING_TESTCPP_NS
///////////////////////////////////////////////////////////
extern "C" TestListener*
testcppxmllistener_create_instance(TestResultReporter* resultReporter,
		TestSuiteResultReporter* suiteReporter,
		TestCaseResultReporter* caseResultReporter) {
	return new XMLTestListener(resultReporter, suiteReporter,
			caseResultReporter);
}

///////////////////////////////////////////////////////////
extern "C" void testcppxmllistener_destroy_instance(TestListener* instance) {
	delete instance;
}

///////////////////////////////////////////////////////////

#include "XMLTestListener.h"
#include "XMLBuilder.h"

#include <fstream>
#include <iostream>

#include <testcpp/utils/Formatter.h>
#include <testcpp/Error.h>
#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestSuiteInfoReader.h>
#include <testcpp/internal/TestFixtureInfoReader.h>

#include <testcpp/runner/TestResultReporter.h>
#include <testcpp/runner/TestSuiteResultReporter.h>
#include <testcpp/runner/TestCaseResultReporter.h>
#include <testcpp/runner/InternalError.h>

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

TESTCPP_NS_START

struct XMLTestListenerImpl
{
	XMLTestListenerImpl(TestResultReporter* testResultReporter
			, TestSuiteResultReporter* testSuiteResultReporter
			, TestCaseResultReporter* testCaseResultReporter
			, std::ostream& os)
		: testResultReporter(testResultReporter)
		, testSuiteResultReporter(testSuiteResultReporter)
		, testCaseResultReporter(testCaseResultReporter)
		, os(os)
	{
		rootElement = XMLBuilder::create("testsuites");
	}

	~XMLTestListenerImpl()
	{
		delete rootElement;
	}

   ////////////////////////////////////////////////////////
	std::ostream& os;
	XMLBuilder* rootElement;
	XMLBuilder* testSuiteElement;
	XMLBuilder* testCaseElement;

   ////////////////////////////////////////////////////////
	TestResultReporter* testResultReporter;
	TestSuiteResultReporter* testSuiteResultReporter;
	TestCaseResultReporter* testCaseResultReporter;

   ////////////////////////////////////////////////////////
   void startTest();
   void endTest();
   void startTestSuite(TestSuiteInfoReader* suite);
   void endTestSuite(TestSuiteInfoReader* suite);
   void endTestCase(TestCaseInfoReader* testcase);
   void addCaseCrash(TestCaseInfoReader* testcase);
   void addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure);
   void addCaseError(TestCaseInfoReader* testcase, const std::string& msg);
};

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::startTest()
{
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::endTest()
{
	rootElement->write(os);
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
startTestSuite(TestSuiteInfoReader* suite)
{
	XMLBuilder& element = rootElement->element("testsuite");
	testSuiteElement = &element;
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
endTestSuite(TestSuiteInfoReader* suite)
{
	testSuiteElement->attribute("name", suite->getName())
		.attribute("tests", toValStr(suite->getNumberOfTestCases()))
		.attribute("fixtures", toValStr(suite->getNumberOfTestFixtures()))
		.attribute("crashes", toValStr(testSuiteResultReporter->getNumberOfCrashedTestCases(suite)))
		.attribute("errors", toValStr(testSuiteResultReporter->getNumberOfErrorTestCases(suite)))
		.attribute("failures", toValStr(testSuiteResultReporter->getNumberOfFailedTestCases(suite)));
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
endTestCase(TestCaseInfoReader* testcase)
{
	XMLBuilder& element = testSuiteElement->element("testcase")
		.attribute("name", testcase->getName())
		.attribute("fixture", testcase->getNameOfFixture())
		.attribute("time", toValStr(0))
		.attribute("filename", testcase->getFileName());
	testCaseElement = &element;
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseCrash(TestCaseInfoReader* testcase)
{
	endTestCase(testcase);
	testCaseElement->element("crash")
		.text("test case crashed unexpectedly.");
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
	endTestCase(testcase);
	testCaseElement->element("error")
		.text(msg);
}

///////////////////////////////////////////////////////////
void XMLTestListenerImpl::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
	endTestCase(testcase);
	testCaseElement->element("failure")
		.text(failure.what());
}

///////////////////////////////////////////////////////////
XMLTestListener::XMLTestListener(
        TestResultReporter* testResultReporter
		, TestSuiteResultReporter* testSuiteResultReporter
		, TestCaseResultReporter* testCaseResultReporter
		, std::ostream& os)
  : This( new XMLTestListenerImpl(testResultReporter
        , testSuiteResultReporter
        , testCaseResultReporter, os))
{
}

///////////////////////////////////////////////////////////
XMLTestListener::~XMLTestListener()
{
	delete This;
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseCrash(TestCaseInfoReader* testcase)
{
	This->addCaseCrash(testcase);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
	This->addCaseError(testcase, msg);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
	This->addCaseFailure(testcase, failure);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
startTestCase(TestCaseInfoReader* testcase)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
endTestCase(TestCaseInfoReader* testcase)
{
   This->endTestCase(testcase);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
startTestFixture(TestFixtureInfoReader* fixtureinfo)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
endTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::
startTestSuite(TestSuiteInfoReader* suite)
{
   This->startTestSuite(suite);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->endTestSuite(suite);
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addSuiteError(TestSuiteInfoReader*, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void XMLTestListener::startTest()
{
   This->startTest();
}

///////////////////////////////////////////////////////////
void XMLTestListener::endTest()
{
	This->endTest();
}

///////////////////////////////////////////////////////////
void XMLTestListener::
addError(const std::string& msg)
{
}

TESTCPP_NS_END

///////////////////////////////////////////////////////////
USING_TESTCPP_NS

namespace
{
  std::ofstream xmlFile;
}

///////////////////////////////////////////////////////////
extern "C"
TestListener* cxxtestplus_xml_listener_create_instance(
      TestResultReporter* resultReporter
    , TestSuiteResultReporter* suiteReporter
    , TestCaseResultReporter* caseResultReporter
    , int argc, char** argv)
{
   if(argc == 1)
   {
	   return new XMLTestListener(resultReporter, suiteReporter,
			  caseResultReporter, std::cout);
   }

   xmlFile.open(argv[1]);
   return new XMLTestListener(resultReporter, suiteReporter,
			  caseResultReporter, xmlFile);
}

///////////////////////////////////////////////////////////
extern "C"
void cxxtestplus_xml_listener_destroy_instance(TestListener* instance)
{
   if(xmlFile.is_open()) xmlFile.close();
	delete instance;
}

///////////////////////////////////////////////////////////

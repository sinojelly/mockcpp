
#include <iostream>

#include <testcpp/runner/SimpleTestResultReporter.h>
#include <testcpp/runner/TestSuiteResultReporter.h>
#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestSuiteInfoReader.h>

TESTCPP_NS_START

struct SimpleTestResultReporterImpl
{
   unsigned int numberOfSuccessfulCases;
   unsigned int numberOfCrashedCases;
   unsigned int numberOfErrorCases;
   unsigned int numberOfFailedCases;
   unsigned int numberOfLoadedSuites;
   unsigned int numberOfUnloadableSuites;
   TestSuiteResultReporter* suiteResultReporter;

   unsigned int getNumberOfUnsuccessfulCases() const;
   unsigned int getNumberOfTestCases() const;

   SimpleTestResultReporterImpl(TestSuiteResultReporter* suiteReporter)
      : numberOfCrashedCases(0)
      , numberOfErrorCases(0)
      , numberOfFailedCases(0)
      , numberOfSuccessfulCases(0)
      , numberOfLoadedSuites(0)
      , numberOfUnloadableSuites(0)
      , suiteResultReporter(suiteReporter)
   {}
};

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporterImpl::
getNumberOfUnsuccessfulCases() const
{
   return numberOfCrashedCases + numberOfErrorCases + numberOfFailedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporterImpl::getNumberOfTestCases() const
{
   return getNumberOfUnsuccessfulCases() + numberOfSuccessfulCases;
}
///////////////////////////////////////////////////////////
SimpleTestResultReporter::
SimpleTestResultReporter(TestSuiteResultReporter* suiteResultReporter)
   : This(new SimpleTestResultReporterImpl(suiteResultReporter))
{
}

///////////////////////////////////////////////////////////
SimpleTestResultReporter::~SimpleTestResultReporter()
{
   delete This;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseCrash(TestCaseInfoReader* testcase)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestCase(TestCaseInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestCase(TestCaseInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure& failure)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestSuite(TestSuiteInfoReader* suite)
{
   This->numberOfLoadedSuites++;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->numberOfSuccessfulCases += \
          This->suiteResultReporter->getNumberOfSuccessfulTestCases(suite);

   This->numberOfCrashedCases += \
          This->suiteResultReporter->getNumberOfCrashedTestCases(suite);

   This->numberOfErrorCases += \
          This->suiteResultReporter->getNumberOfErrorTestCases(suite);

   This->numberOfFailedCases += \
          This->suiteResultReporter->getNumberOfFailedTestCases(suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addSuiteError(TestSuiteInfoReader*, const std::string& msg )
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTest()
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTest()
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addError(const std::string& msg)
{
   This->numberOfUnloadableSuites++;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfTestCases() const
{
   return This->getNumberOfTestCases();
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfSuccessfulTestCases() const
{
   return This->numberOfSuccessfulCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfUnsuccessfulTestCases() const
{
   return This->getNumberOfUnsuccessfulCases(); 
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfFailedTestCases() const
{
   return This->numberOfFailedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfErrorTestCases() const
{
   return This->numberOfErrorCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfCrashedTestCases() const
{
   return This->numberOfCrashedCases;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestResultReporter::
getNumberOfUnloadableSuites() const
{
   return This->numberOfUnloadableSuites;
}

unsigned int
SimpleTestResultReporter::
getNumberOfLoadedSuites() const
{
   return This->numberOfLoadedSuites;
}

///////////////////////////////////////////////////////////

TESTCPP_NS_END


#include <iostream>

#include <testcpp/runner/SimpleTestResultReporter.h>
#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestSuiteInfoReader.h>

TESTCPP_NS_START

struct SimpleTestResultReporterImpl
{
   enum {
      SUCCESS = 0,
      FAILED  = 1,
      ERROR   = 2
   };

   int currentCaseStatus;
   unsigned int numberOfSuccessfulCases;
   unsigned int numberOfCrashedCases;
   unsigned int numberOfErrorCases;
   unsigned int numberOfFailedCases;
   unsigned int numberOfUnloadableSuites;

   unsigned int getNumberOfUnsuccessfulCases() const;
   unsigned int getNumberOfTestCases() const;

   SimpleTestResultReporterImpl()
      : numberOfCrashedCases(0)
      , numberOfErrorCases(0)
      , numberOfFailedCases(0)
      , numberOfSuccessfulCases(0)
      , numberOfUnloadableSuites(0)
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
SimpleTestResultReporter()
   : This(new SimpleTestResultReporterImpl())
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
   This->numberOfCrashedCases++;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
   This->currentCaseStatus = SimpleTestResultReporterImpl::ERROR;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   This->currentCaseStatus = SimpleTestResultReporterImpl::FAILED;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
startTestCase(TestCaseInfoReader*)
{
   This->currentCaseStatus = SimpleTestResultReporterImpl::SUCCESS;
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestCase(TestCaseInfoReader*)
{
   switch(This->currentCaseStatus)
   {
   case SimpleTestResultReporterImpl::SUCCESS:
      This->numberOfSuccessfulCases++;
      break;
   case SimpleTestResultReporterImpl::FAILED:
      This->numberOfFailedCases++;
      break;
   case SimpleTestResultReporterImpl::ERROR:
      This->numberOfErrorCases++;
      break;
   }
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
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
endTestSuite(TestSuiteInfoReader* suite)
{
}

///////////////////////////////////////////////////////////
void SimpleTestResultReporter::
addSuiteError(TestSuiteInfoReader*, const std::string& msg )
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

///////////////////////////////////////////////////////////

TESTCPP_NS_END

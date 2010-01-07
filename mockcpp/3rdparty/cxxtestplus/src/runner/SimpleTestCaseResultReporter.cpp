
#include <iostream>

#include <testcpp/Error.h>

#include <testcpp/runner/SimpleTestCaseResultReporter.h>
#include <testcpp/runner/InternalError.h>

TESTCPP_NS_START

struct SimpleTestCaseResultReporterImpl
{
   TestCaseInfoReader* testcase;
   bool informedError;
   bool informedFailure;
   bool informedCrashed;
   bool finished;

   SimpleTestCaseResultReporterImpl()
      : testcase(0)
      , informedError(false)
      , informedFailure(false)
      , informedCrashed(false)
      , finished(false)
   {}
};

///////////////////////////////////////////////////////////
SimpleTestCaseResultReporter::
SimpleTestCaseResultReporter()
   : This(new SimpleTestCaseResultReporterImpl())
{
}

///////////////////////////////////////////////////////////
SimpleTestCaseResultReporter::~SimpleTestCaseResultReporter()
{
   delete This;
}

///////////////////////////////////////////////////////////
unsigned int
SimpleTestCaseResultReporter::getTestCaseResult(TestCaseInfoReader* testcase) const
{
   if(testcase == This->testcase && This->finished) 
   {
      if(This->informedCrashed) return TestCaseResultReporter::CRASHED;
      if(This->informedError) return TestCaseResultReporter::ERROR;
      if(This->informedFailure) return TestCaseResultReporter::FAILED;

      return TestCaseResultReporter::SUCCESS;
   }

   return TestCaseResultReporter::UNKNOWN;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseCrash(TestCaseInfoReader* testcase)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->finished = true;
   This->informedCrashed = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->informedError = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->informedFailure = true;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
startTestCase(TestCaseInfoReader* testcase)
{
   if(This->testcase != 0 && !This->finished)
   {
      throw Error(TESTCPP_INTERNAL_ERROR(2001));
   }

   This->testcase = testcase;
   This->informedError = false;
   This->informedFailure = false;
   This->informedCrashed = false;
   This->finished = false;
}

///////////////////////////////////////////////////////////
void SimpleTestCaseResultReporter::
endTestCase(TestCaseInfoReader* testcase)
{
   if(This->testcase != testcase)
   {
      return;
   }

   This->finished = true;
}

///////////////////////////////////////////////////////////

TESTCPP_NS_END


#include <testcpp/runner/SimpleTestCaseRunner.h>
#include <testcpp/runner/TestCaseResultCollector.h>
#include <testcpp/internal/TestCase.h>
#include <testcpp/internal/TestFixtureDesc.h>

TESTCPP_NS_START

void SimpleTestCaseRunner::run(TestFixtureDesc* desc
      , TestCase* testcase
      , TestCaseResultCollector* collector)
{
   collector->startTestCase(testcase);
   bool errorOccurred = false;

   try {
      desc->getFixture()->setUp();
      testcase->run();
   }
   catch(AssertionFailure& failure)
   {
      errorOccurred = true;
      collector->addCaseFailure(testcase, failure);
   }
   catch(std::exception& e)
   {
      errorOccurred = true;
      collector->addCaseError(testcase, e.what());
   }
   catch(...)
   {
      errorOccurred = true;
      collector->addCaseError(testcase, "Unknown Exception");
   }

   try {
      desc->getFixture()->tearDown();
   }
   catch(AssertionFailure& failure)
   {
      if(!errorOccurred)
         collector->addCaseFailure(testcase, failure);
   }
   catch(std::exception& e)
   {
      if(!errorOccurred)
         collector->addCaseError(testcase, e.what());
   }
   catch(...)
   {
      if(!errorOccurred)
         collector->addCaseError(testcase, "Unknown Exception");
   }
 
   collector->endTestCase(testcase);
}

TESTCPP_NS_END



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

   try {
      desc->getFixture()->setUp();
      testcase->run();
      desc->getFixture()->tearDown();
   }
   catch(AssertionFailure& failure)
   {
      collector->addCaseFailure(testcase, failure);
   }
   catch(std::exception& e)
   {
      collector->addCaseError(testcase, e.what());
   }
   catch(...)
   {
      collector->addCaseError(testcase, "Unknown Exception");
   }

   collector->endTestCase(testcase);
}

TESTCPP_NS_END


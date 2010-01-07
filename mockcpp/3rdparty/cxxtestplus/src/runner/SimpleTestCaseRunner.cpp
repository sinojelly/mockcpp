
#include <testcpp/runner/SimpleTestCaseRunner.h>
#include <testcpp/runner/TestCaseResultCollector.h>
#include <testcpp/internal/TestCase.h>
#include <testcpp/internal/TestFixtureDesc.h>
#include <testcpp/TestCaseSuccess.h>

TESTCPP_NS_START

#define __RUN(block) try block \
   catch(TESTCPP_NS::TestCaseSuccess& e) \
   { \
   } \
   catch(AssertionFailure& failure) \
   { \
      collector->addCaseFailure(testcase, failure); \
   } \
   catch(std::exception& e) \
   { \
      collector->addCaseError(testcase, e.what()); \
   } \
   catch(...) \
   { \
      collector->addCaseError(testcase, "Unknown Exception"); \
   }

void SimpleTestCaseRunner::run(TestFixtureDesc* desc
      , TestCase* testcase
      , TestCaseResultCollector* collector)
{
   collector->startTestCase(testcase);

   __RUN({
      desc->getFixture()->setUp();
      testcase->run();
   });

   __RUN({
      desc->getFixture()->tearDown();
   });

   collector->endTestCase(testcase);
}

TESTCPP_NS_END


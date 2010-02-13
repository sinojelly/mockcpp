
#include <testngpp/internal/TestCase.h>
#include <testngpp/runner/TestCaseResultCollector.h>
#include <testngpp/runner/TestCaseRunnerDieHandler.h>

TESTNGPP_NS_START

void TestCaseRunnerDieHandler::
die(TestCase* testcase, TestCaseResultCollector* collector)
{
   collector->addCaseCrash(testcase);
}

TESTNGPP_NS_END

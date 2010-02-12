
#include <testngpp/win32/Die.h>
#include <testngpp/runner/TestCaseRunnerDieHandler.h>

TESTNGPP_NS_START

void TestCaseRunnerDieHandler::
die(TestCase* testcase, TestCaseResultCollector* collector)
{
   throw Die();
}

TESTNGPP_NS_END
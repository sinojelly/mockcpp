
#ifndef __TESTCPP_TEST_FIXTURE_SANDBOX_RUNNER_H
#define __TESTCPP_TEST_FIXTURE_SANDBOX_RUNNER_H

#include <testcpp/testcpp.h>
#include <testcpp/runner/TestFixtureRunner.h>

TESTCPP_NS_START

struct TestFixtureDesc;
struct TestCaseRunner;
struct TestFixtureResultCollector;
struct TestFixtureSandboxRunnerImpl;

struct TestFixtureSandboxRunner
   : public TestFixtureRunner
{
   TestFixtureSandboxRunner(
       unsigned int maxCurrentProcess
       , TestCaseRunner*);

   ~TestFixtureSandboxRunner();

	void run ( TestFixtureDesc*
            , TestFixtureResultCollector*
            , const TestCaseFilter*); 

private:
   TestFixtureSandboxRunnerImpl* This;
};

TESTCPP_NS_END

#endif


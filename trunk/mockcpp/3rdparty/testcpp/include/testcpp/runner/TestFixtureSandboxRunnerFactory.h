
#ifndef __TESTCPP_TEST_FIXTURE_SANDBOX_RUNNER_FACTORY_H
#define __TESTCPP_TEST_FIXTURE_SANDBOX_RUNNER_FACTORY_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixtureRunner;

struct TestFixtureSandboxRunnerFactory
{
   static
   TestFixtureRunner* createInstance(unsigned int maxConcurrent);

   static
   void destroyInstance(TestFixtureRunner* instance);

private:

   TestFixtureSandboxRunnerFactory();
};

TESTCPP_NS_END

#endif



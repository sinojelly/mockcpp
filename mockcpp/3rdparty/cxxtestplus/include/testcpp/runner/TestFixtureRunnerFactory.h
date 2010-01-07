
#ifndef __TESTCPP_TEST_FIXTURE_RUNNER_FACTORY_H
#define __TESTCPP_TEST_FIXTURE_RUNNER_FACTORY_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixtureRunner;

struct TestFixtureRunnerFactory
{
   static
   TestFixtureRunner* createInstance(bool useSandbox
                     , unsigned int maxConcurrent);

   static
   void destroyInstance(TestFixtureRunner* instance);

private:

   TestFixtureRunnerFactory();
};

TESTCPP_NS_END

#endif



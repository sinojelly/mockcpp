
#ifndef __TESTNGPPST_TEST_FIXTURE_RUNNER_FACTORY_H
#define __TESTNGPPST_TEST_FIXTURE_RUNNER_FACTORY_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

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

TESTNGPPST_NS_END

#endif



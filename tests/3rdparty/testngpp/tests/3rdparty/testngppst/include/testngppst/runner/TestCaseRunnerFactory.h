
#ifndef __TESTNGPPST_TESTCASE_RUNNER_FACTORY_H
#define __TESTNGPPST_TESTCASE_RUNNER_FACTORY_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCaseRunner;

struct TestCaseRunnerFactory
{
   static TestCaseRunner* createInstance();
   static void releaseInstance(TestCaseRunner* runner);
};

TESTNGPPST_NS_END

#endif

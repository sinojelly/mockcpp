
#ifndef __TESTNGPPST_TEST_SUITE_RESULT_DISPATCHER_H
#define __TESTNGPPST_TEST_SUITE_RESULT_DISPATCHER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestSuiteListener;

struct TestSuiteResultDispatcher
{
   virtual void registerTestSuiteListener(TestSuiteListener* listener) = 0;
   virtual TestSuiteListener* unregisterTestSuiteListener(TestSuiteListener* listener) = 0;

   virtual ~TestSuiteResultDispatcher() {}
};

TESTNGPPST_NS_END

#endif


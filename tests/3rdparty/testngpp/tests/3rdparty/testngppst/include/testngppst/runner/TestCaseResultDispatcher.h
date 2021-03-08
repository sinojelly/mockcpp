
#ifndef __TESTNGPPST_TEST_CASE_RESULT_DISPATCHER_H
#define __TESTNGPPST_TEST_CASE_RESULT_DISPATCHER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCaseListener;

struct TestCaseResultDispatcher
{
   virtual void registerTestCaseListener(TestCaseListener* listener) = 0;
   virtual TestCaseListener* unregisterTestCaseListener(TestCaseListener* listener) = 0;

   virtual ~TestCaseResultDispatcher() {}
};

TESTNGPPST_NS_END

#endif


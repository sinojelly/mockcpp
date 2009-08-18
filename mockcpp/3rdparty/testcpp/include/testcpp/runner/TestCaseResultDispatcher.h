
#ifndef __TESTCPP_TEST_CASE_RESULT_DISPATCHER_H
#define __TESTCPP_TEST_CASE_RESULT_DISPATCHER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestCaseListener;

struct TestCaseResultDispatcher
{
   virtual void registerTestCaseListener(TestCaseListener* listener) = 0;
   virtual TestCaseListener* unregisterTestCaseListener(TestCaseListener* listener) = 0;

   virtual ~TestCaseResultDispatcher() {}
};

TESTCPP_NS_END

#endif


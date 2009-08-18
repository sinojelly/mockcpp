
#ifndef __TESTCPP_TEST_RESULT_DISPATCHER_H
#define __TESTCPP_TEST_RESULT_DISPATCHER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestListener;

struct TestResultDispatcher
{
   virtual void registerListener(TestListener* listener) = 0;
   virtual ~TestResultDispatcher() {}
};

TESTCPP_NS_END

#endif


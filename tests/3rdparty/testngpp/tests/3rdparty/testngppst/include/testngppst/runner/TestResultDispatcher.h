
#ifndef __TESTNGPPST_TEST_RESULT_DISPATCHER_H
#define __TESTNGPPST_TEST_RESULT_DISPATCHER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestListener;

struct TestResultDispatcher
{
   virtual void registerListener(TestListener* listener) = 0;
   virtual ~TestResultDispatcher() {}
};

TESTNGPPST_NS_END

#endif


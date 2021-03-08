
#ifndef __TESTNGPPST_TEST_CASE_LISTENER_H
#define __TESTNGPPST_TEST_CASE_LISTENER_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestCaseResultCollector.h>

TESTNGPPST_NS_START

struct TestCaseListener
   : public TestCaseResultCollector
{
   virtual ~TestCaseListener() {}
};

TESTNGPPST_NS_END

#endif


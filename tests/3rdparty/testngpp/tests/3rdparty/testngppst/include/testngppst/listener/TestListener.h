
#ifndef __TESTNGPPST_TEST_LISTENER_H
#define __TESTNGPPST_TEST_LISTENER_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestResultCollector.h>

TESTNGPPST_NS_START

struct TestListener
   : public TestResultCollector
{
   virtual ~TestListener() {}
};

TESTNGPPST_NS_END

#endif


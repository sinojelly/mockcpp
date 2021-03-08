
#ifndef __TESTNGPPST_TEST_SUITE_LISTENER_H
#define __TESTNGPPST_TEST_SUITE_LISTENER_H

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestSuiteResultCollector.h>

TESTNGPPST_NS_START

struct TestSuiteListener
   : public TestSuiteResultCollector
{
   virtual ~TestSuiteListener() {}
};

TESTNGPPST_NS_END

#endif


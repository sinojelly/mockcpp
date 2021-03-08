
#ifndef __TESTNGPPST_TEST_LISTENER_LOADER_FACTORY_H
#define __TESTNGPPST_TEST_LISTENER_LOADER_FACTORY_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestListenerLoader;
struct TestResultReporter;
struct TestSuiteResultReporter;
struct TestCaseResultReporter;

struct TestListenerLoaderFactory
{
   virtual TestListenerLoader* create() = 0;

	virtual ~TestListenerLoaderFactory() {}
};

TESTNGPPST_NS_END

#endif


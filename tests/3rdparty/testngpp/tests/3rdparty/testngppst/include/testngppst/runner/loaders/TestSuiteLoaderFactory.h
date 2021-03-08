
#ifndef __TESTNGPPST_TEST_SUITE_LOADER_FACTORY_H
#define __TESTNGPPST_TEST_SUITE_LOADER_FACTORY_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestSuiteLoader;

struct TestSuiteLoaderFactory
{
   virtual TestSuiteLoader* create() = 0;

	virtual ~TestSuiteLoaderFactory() {}
};

TESTNGPPST_NS_END

#endif


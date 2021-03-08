
#ifndef __TESTNGPPST_MODULE_SUITE_LOADER_FACTORY_H
#define __TESTNGPPST_MODULE_SUITE_LOADER_FACTORY_H

#include <testngppst/testngppst.h>

#include <testngppst/runner/loaders/TestSuiteLoaderFactory.h>

TESTNGPPST_NS_START

struct ModuleTestSuiteLoaderFactory
   : public TestSuiteLoaderFactory
{
   TestSuiteLoader* create();
};

TESTNGPPST_NS_END

#endif


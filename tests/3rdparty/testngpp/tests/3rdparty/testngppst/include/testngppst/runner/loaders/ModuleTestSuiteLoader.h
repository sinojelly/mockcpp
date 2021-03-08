
#ifndef __TESTNGPPST_MODULE_TEST_SUITE_LOADER_H
#define __TESTNGPPST_MODULE_TEST_SUITE_LOADER_H

#include <testngppst/testngppst.h>

#include <testngppst/runner/loaders/TestSuiteLoader.h>

TESTNGPPST_NS_START

struct ModuleLoader;
struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;
struct ModuleTestSuiteLoaderImpl;

struct ModuleTestSuiteLoader : public TestSuiteLoader
{
   ModuleTestSuiteLoader(ModuleLoader* loader);
   ~ModuleTestSuiteLoader();

	TestSuiteDesc*
   load( const StringList& searchingPaths
       , const std::string& path
       , TestSuiteDescEntryNameGetter* nameGetter);

   void unload();

private:
   ModuleTestSuiteLoaderImpl* This;
};

TESTNGPPST_NS_END

#endif



#ifndef __TESTNGPPST_MODULE_TEST_LISTENER_LOADER_H
#define __TESTNGPPST_MODULE_TEST_LISTENER_LOADER_H

#include <list>

#include <testngppst/testngppst.h>

#include <testngppst/runner/loaders/TestListenerLoader.h>

TESTNGPPST_NS_START

struct ModuleLoader;
struct ModuleTestListenerLoaderImpl;

struct ModuleTestListenerLoader : public TestListenerLoader
{
   ModuleTestListenerLoader(ModuleLoader* loader);
   ~ModuleTestListenerLoader();

   TestListener*
   load( const StringList& SearchingPaths
       , const std::string& commandLine
       , TestResultReporter* resultReporter
       , TestSuiteResultReporter* suiteResultReporter
       , TestCaseResultReporter* caseResultReporter);

private:

   ModuleTestListenerLoaderImpl* This;

};

TESTNGPPST_NS_END

#endif


#ifndef __TESTNGPPST_TEST_RUNNER_H
#define __TESTNGPPST_TEST_RUNNER_H

#include <string>

#include <testngppst/testngppst.h>

#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct TestRunnerImpl;

struct TestRunner
{
public:
   TestRunner();
   ~TestRunner();

   int runTests( bool useSandboxRunner
               , unsigned int maxConcurrent
               , const StringList& suitePaths
               , const StringList& listenerNames
               , const StringList& searchingPathsOfListeners
               , const StringList& fixtures
               , const std::string& tagsFilterOption);

private:
   TestRunnerImpl * This;

};

TESTNGPPST_NS_END

#endif


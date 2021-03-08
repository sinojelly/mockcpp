
#ifndef __TESTNGPPST_TEST_RUNNER_CONTEXT_H
#define __TESTNGPPST_TEST_RUNNER_CONTEXT_H

#include <testngppst/testngppst.h>
#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct TestSuiteContext;
struct TestFilter;
struct TagsFilters;
struct TestResultCollector;

struct TestRunnerContextImpl;

/////////////////////////////////////////////////////////////////
struct TestRunnerContext
{
   TestRunnerContext
      ( const StringList& nameOfSuites
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestRunnerContext();

   TestSuiteContext* getSuite(unsigned int index) const;
   unsigned int numberOfSuites() const;

private:

   TestRunnerContextImpl * This;

};

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif


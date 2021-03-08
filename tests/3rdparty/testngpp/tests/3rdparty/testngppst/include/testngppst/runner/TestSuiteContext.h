
#ifndef __TESTNGPPST_TEST_SUITE_CONTEXT_H
#define __TESTNGPPST_TEST_SUITE_CONTEXT_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestSuiteLoader;
struct TestFixtureContext;
struct TestFilter;
struct TagsFilters;
struct TestSuiteDesc;
struct TestResultCollector;

struct TestSuiteContextImpl;

/////////////////////////////////////////////////////////////////
struct TestSuiteContext
{
   TestSuiteContext
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestSuiteContext();

   const std::string& getSuitePath() const;
   TestSuiteDesc* getSuite() const;
   unsigned int numberOfFixtures() const;
   TestFixtureContext* getFixture(unsigned int index) const;

private:

   TestSuiteContextImpl * This;

};

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif


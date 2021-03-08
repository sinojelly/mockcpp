
#include <iostream>
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/TestSuiteContext.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/loaders/ModuleTestSuiteLoader.h>
#include <testngpp/runner/loaders/DLModuleLoader.h>
#include <testngpp/runner/TagsParser.h>
#include <testngpp/runner/TagsFilters.h>
#include <testngpp/listener/TestResultCollector.h>


USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestTestSuiteContext: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   TestSuiteContext* context;
 
   MockObject<TestResultCollector> collector;
   MockObject<TestFilter> filter;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      MOCK_METHOD(filter, isFixtureMatch).stubs().will(returnValue(true));
      MOCK_METHOD(filter, isCaseMatch).stubs().will(returnValue(true));
   }

   void tearDown()
   {
      filter.reset();
      collector.reset();

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldNotHaveMemoryLeakage()
   {
      TagsFilters* tagsFilter = TagsParser::parse("*");

      context = new TestSuiteContext
         ( new ModuleTestSuiteLoader(new DLModuleLoader())
         , "../../build_testngpp/samples/libsample"
         , collector
         , tagsFilter
         , filter);

      delete tagsFilter;

      delete context;
   }
};

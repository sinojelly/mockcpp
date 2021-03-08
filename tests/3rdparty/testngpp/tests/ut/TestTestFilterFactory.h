
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/TestFilterFactory.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestCaseInfoReader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestTestFilterFactory: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
   }
   void tearDown()
   {
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldReturnAWildcardFilterIfNoFilterOptionsSpecified()
   {
      StringList filterOptions;

      const TestFilter* filter = TestFilterFactory::getFilter(filterOptions);

      TS_ASSERT(filter != 0);

      /////////////////////////////////////////////////
      MockObject<TestFixtureInfoReader> fixture;

      fixture.METHOD(TestFixtureInfoReader::getName)
             .stubs().will(returnValue(std::string("stupidNameOrWhatever")));

      TS_ASSERT(filter->isFixtureMatch(fixture));

      /////////////////////////////////////////////////
      MockObject<TestCaseInfoReader> testcase;

      testcase.METHOD(TestCaseInfoReader::getName)
             .stubs().will(returnValue(std::string("stupidNameOrWhatever")));

      TS_ASSERT(filter->isCaseMatch((const TestCase*)(const TestCaseInfoReader*)testcase));

      //////////////////////////////////////////////////
      TestFilterFactory::returnFilter(filter);
   }

   void testShouldReturnACapableFilterIfThereAreFilterOptionsSpecified()
   {
      StringList filterOptions;
      filterOptions.add("Fixture1:testcase0");

      const TestFilter* filter = TestFilterFactory::getFilter(filterOptions);

      TS_ASSERT(filter != 0);


      /////////////////////////////////////////////////
      MockObject<TestFixtureInfoReader> fixture0;

      MOCK_METHOD(fixture0, getName)
              .stubs().will(returnValue(std::string("Fixture0")));

      TS_ASSERT(!filter->isFixtureMatch(fixture0));

      //////////////////////////////////////////////////
      MockObject<TestFixtureInfoReader> fixture2;

      fixture2.METHOD(TestFixtureInfoReader::getName)
              .stubs().will(returnValue(std::string("Fixture2")));

      TS_ASSERT(!filter->isFixtureMatch(fixture2));

      //////////////////////////////////////////////////
      MockObject<TestFixtureInfoReader> fixture1;

      fixture1.METHOD(TestFixtureInfoReader::getName)
              .stubs().will(returnValue(std::string("Fixture1")));

      TS_ASSERT(filter->isFixtureMatch(fixture1));

      //////////////////////////////////////////////////
      TestFilterFactory::returnFilter(filter);

   }
};

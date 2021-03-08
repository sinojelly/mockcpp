
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/GeneralTestFilter.h>
#include <testngpp/runner/NameMatcher.h>
#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestCaseInfoReader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestGeneralTestFilter: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   TestFilter* filter;

   MockObject<NameMatcher> fixtureMatcher;
   MockObject<NameMatcher> caseMatcher;
   MockObject<TestFixtureInfoReader> fixture;
   MockObject<TestCaseInfoReader> testcase;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      filter = new GeneralTestFilter(fixtureMatcher, caseMatcher);

      std::string fixtureName = "TestFixture";
      std::string caseName = "TestCase";

      fixture.METHOD(TestFixtureInfoReader::getName)
             .defaults().will(returnValue(fixtureName));

      testcase.METHOD(TestCaseInfoReader::getName)
             .defaults().will(returnValue(caseName));

      testcase.METHOD(TestCaseInfoReader::getNameOfFixture)
             .defaults().will(returnValue(fixtureName));

      fixtureMatcher.METHOD(NameMatcher::matches)
             .defaults().with(eq(fixtureName))
             .will(returnValue(true));

      fixtureMatcher.METHOD(NameMatcher::matches)
             .defaults().with(neq(fixtureName))
             .will(returnValue(false));

      caseMatcher.METHOD(NameMatcher::matches)
             .defaults().with(eq(caseName))
             .will(returnValue(true));

      caseMatcher.METHOD(NameMatcher::matches)
             .defaults().with(neq(caseName))
             .will(returnValue(false));
   }

   void tearDown()
   {
      fixture.reset();
      testcase.reset();
      fixtureMatcher.reset();
      caseMatcher.reset();

      delete filter;

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToTellIfSpecifiedTestFixtureMatches()
   {
      TS_ASSERT(filter->isFixtureMatch(fixture));
      TS_ASSERT(filter->isCaseMatch((const TestCase*)(const TestCaseInfoReader*)testcase));
   }

   
};

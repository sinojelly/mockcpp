
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/OrCompositeTestFilter.h>
#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestCaseInfoReader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestOrCompositeTestFilter: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   MockObject<TestFixtureInfoReader> fixture;
   MockObject<TestCaseInfoReader> testcase;

   MockObject<TestFilter> filter1;
   MockObject<TestFilter> filter2;
   MockObject<TestFilter> filter3;

   OrCompositeTestFilter* filter;
public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      filter1.METHOD(TestFilter::isFixtureMatch)
         .defaults().will(returnValue(false));

      filter1.METHOD(TestFilter::isCaseMatch)
         .defaults().will(returnValue(false));

      filter2.METHOD(TestFilter::isFixtureMatch)
         .defaults().will(returnValue(false));

      filter2.METHOD(TestFilter::isCaseMatch)
         .defaults().will(returnValue(false));

      filter3.METHOD(TestFilter::isFixtureMatch)
         .defaults().will(returnValue(false));

      filter3.METHOD(TestFilter::isCaseMatch)
         .defaults().will(returnValue(false));

      filter = new OrCompositeTestFilter();

      filter->addFilter(filter1);
      filter->addFilter(filter2);
      filter->addFilter(filter3);
   }

   void tearDown()
   {
      delete filter;

      filter1.reset();
      filter2.reset();
      filter3.reset();

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldMatchesAFixutreIfAnyOfAddedFiltersMatchesIt()
   {
      filter2.METHOD(TestFilter::isFixtureMatch)
         .stubs()
         .with(eq((const TestFixtureInfoReader*)fixture))
         .will(returnValue(true));

      TS_ASSERT(filter->isFixtureMatch(fixture));
   }

   void testShouldNotMatchAFixtureIfAllAddedFiltersClaimsNotMatch()
   {
      TS_ASSERT(!filter->isFixtureMatch(fixture));
   }

   void testShouldMatchesATestcaseIfAnyOfAddedFiltersMatchesIt()
   {
      const TestCase* tc = (const TestCase*)(const TestCaseInfoReader*)testcase;
      filter2.METHOD(TestFilter::isCaseMatch)
         .stubs()
         .with(eq(tc))
         .will(returnValue(true));

      TS_ASSERT(filter->isCaseMatch(tc));
   }

   void testShouldNotMatchATestcaseIfAllAddedFiltersClaimsNotMatch()
   {
      const TestCase* tc = (const TestCase*)(const TestCaseInfoReader*)testcase;
      TS_ASSERT(!filter->isCaseMatch(tc));
   }

   void testShouldDeleteAllTestFiltersWhichAreAddedAsComposite()
   {
      filter1.willBeDeleted();
      filter2.willKeepAlive();
      filter3.willBeDeleted();

      OrCompositeTestFilter* thisFilter = new OrCompositeTestFilter();

      thisFilter->addFilter(filter1, true);
      thisFilter->addFilter(filter2);
      thisFilter->addFilter(filter3, true);

      delete thisFilter;

      filter1.verify();
      filter2.verify();
      filter3.verify();
   }
};

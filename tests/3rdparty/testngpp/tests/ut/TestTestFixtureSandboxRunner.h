
#include <cxxtest/TestSuite.h> 
#include <testngppst/runner/ResourceCheckPoint.h>

#include <mockcpp/mockcpp.hpp>

#include <TestFixtureDef.h>

#include <testngpp/runner/TestHierarchySandboxRunner.h>
#include <testngpp/runner/TestHierarchyRunner.h>
#include <testngpp/runner/TestHierarchyHandler.h>
#include <testngpp/runner/SimpleTestCaseRunner.h>
#include <testngpp/listener/TestFixtureResultCollector.h>
#include <testngpp/runner/TestCaseFilter.h>

//FIXME: avoid linux load error, undefined symbol: _ZN8testngpp11StupidTimer4stopEv
#include "../../src/utils/StupidTimer.cpp"

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestTestHierarchySandboxRunner: public CxxTest::TestSuite
{
private:
   TESTNGPPST_RCP checkpoint;

   MockObject<TestCaseFilter> filter;
   MockObject<TestFixtureResultCollector> collector;

public:
   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      MOCK_METHOD(filter, isCaseMatch)
         .defaults().will(returnValue(true));
   }

   void tearDown()
   {
      collector.reset();
      filter.reset();

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToRunATestFixture()
   {
      MOCK_METHOD(collector, startTestCase)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase1))
               .id("start1");

      MOCK_METHOD(collector, addCaseFailure)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase1))
               .after("start1")
               .id("failure1");

      MOCK_METHOD(collector, endTestCase)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase1))
               .after("failure1")
               .id("end1");

      MOCK_METHOD(collector, startTestCase)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase2))
               .id("start2");

      MOCK_METHOD(collector, addCaseError)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase2))
               .after("start2")
               .id("error2");

      MOCK_METHOD(collector, endTestCase)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase2))
               .after("error2")
               .id("end2");

      MOCK_METHOD(collector, startTestCase)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase3))
               .id("start3");

      MOCK_METHOD(collector, endTestCase)
               .expects(once())
               .with(eq((const TestCaseInfoReader*)&myTestCase3))
               .after("start3");

      SimpleTestCaseRunner caseRunner;
      TestHierarchySandboxRunner runner(2, &caseRunner);
//      TestHierarchyHandler hierarchy(&myTestFixtureDesc, filter, collector);
//      runner.run(&hierarchy, collector);
   }
};

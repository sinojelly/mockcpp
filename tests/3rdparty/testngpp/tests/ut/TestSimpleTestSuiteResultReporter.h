
#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/SimpleTestSuiteResultReporter.h>
#include <testngpp/listener/TestCaseResultReporter.h>
#include <testngpp/internal/TestSuiteInfoReader.h>
#include <testngpp/internal/TestCaseInfoReader.h>

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestSimpleTestSuiteResultReporter: public CxxTest::TestSuite
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

   void testShouldBeAbleToReportNumberOfCrashedCases()
   {

//      MockObject<TESTNGPP_NS::TestCaseResultReporter> caseReporter;
//      MockObject<TESTNGPP_NS::TestCaseInfoReader> caseInfoReader;
      MockObject<TESTNGPP_NS::TestSuiteInfoReader> suiteInfoReader;

#if 0
      MOCK_METHOD(caseReporter, getTestCaseResult)
                  .stubs()
                  .will(returnValue((unsigned int)testngpp::TestCaseResultReporter::TR_CRASHED));

      SimpleTestSuiteResultReporter suiteReporter(caseReporter);

      suiteReporter.startTestSuite(suiteInfoReader);

      suiteReporter.startTestCase(caseInfoReader);
      suiteReporter.addCaseCrash(caseInfoReader);
      suiteReporter.endTestCase(caseInfoReader, 0, 0);

      suiteReporter.startTestCase(caseInfoReader);
      suiteReporter.addCaseCrash(caseInfoReader);
      suiteReporter.endTestCase(caseInfoReader, 0, 0);

      suiteReporter.startTestCase(caseInfoReader);
      suiteReporter.addCaseCrash(caseInfoReader);
      suiteReporter.endTestCase(caseInfoReader, 0, 0);

      suiteReporter.endTestSuite(suiteInfoReader);

      TS_ASSERT_EQUALS(3, suiteReporter.getNumberOfCrashedTestCases(suiteInfoReader));
#endif
   }
};

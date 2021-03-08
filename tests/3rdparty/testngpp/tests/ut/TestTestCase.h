
#include <cxxtest/TestSuite.h> 

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/internal/TestCase.h>

#include "MyTestCase.h"

USING_TESTNGPP_NS

class TestTestCase: public CxxTest::TestSuite
{
private:
   TESTNGPPST_RCP checkpoint;

   TestCase* testCase;

public:
   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
	    testCase = new MyTestCase("testShouldDoNothing", "TestNothing", "TestNothing.h", 23);
   }
   void tearDown()
   {
      delete testCase;
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToGetFileName()
   {
      TS_ASSERT_EQUALS(std::string("TestNothing.h"), testCase->getFileName());
   }

   void testShouldBeAbleToGetTestCaseName()
   {
      TS_ASSERT_EQUALS(std::string("testShouldDoNothing"), testCase->getName());
   }

   void testShouldBeAbleToGetTestFixtureName()
   {
      TS_ASSERT_EQUALS(std::string("TestNothing"), testCase->getNameOfFixture());
   }

   void testShouldBeAbleToGetLineOfFile()
   {
      TS_ASSERT_EQUALS((unsigned int)23, testCase->getLineOfFile());
   }

   void testShouldImplementTestCaseInfoReader()
   {
      TS_ASSERT(dynamic_cast<TestCaseInfoReader*>(testCase) != 0);
   }
};

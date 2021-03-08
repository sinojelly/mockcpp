
#include <cxxtest/TestSuite.h> 

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/internal/TestFixtureDesc.h>
#include <testngpp/internal/TestCase.h>

#include "MyTestCase.h"

USING_TESTNGPP_NS

class TestTestFixtureDesc: public CxxTest::TestSuite
{
private:
   TESTNGPPST_RCP checkpoint;

   TestFixtureDesc* desc;
   
   TestCase* testCases[2];

public:
   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      testCases[0] = new MyTestCase("testCase0", "TestNothing", "TestNothing.h", 1);
      testCases[1] = new MyTestCase("testCase1", "TestNothing", "TestNothing.h", 11);

      desc = new TestFixtureDesc("TestNothing" , "TestNothing.h" , testCases , 2);
   }
   void tearDown()
   {
      delete desc;
      delete testCases[0];
      delete testCases[1];
  
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToGetFileNameOfFixture()
   {
      TS_ASSERT_EQUALS(std::string("TestNothing.h"), desc->getFileName());
   }

   void testShouldBeAbleToGetFixtureName()
   {
      TS_ASSERT_EQUALS(std::string("TestNothing"), desc->getName());
   }

   void testShouldBeAbleToGetNumberOfTestCases()
   {
      TS_ASSERT_EQUALS((unsigned int)2, desc->getNumberOfTestCases());
   }

   void testShouldBeAbleToGetTestCaseByIndex()
   {
      TS_ASSERT_EQUALS(testCases[0], desc->getTestCase(0));
      TS_ASSERT_EQUALS(testCases[1], desc->getTestCase(1));
   }

   void testShouldGetNullPointerIfTryingToGetTestCaseWithIndexWhichExceedsTheNumberOfTestCases()
   {
      TS_ASSERT_EQUALS((TestCase*)0, desc->getTestCase(2));
   }

   void testShouldImplementTestFixtureInfoReader()
   {
      TS_ASSERT(dynamic_cast<TestFixtureInfoReader*>(desc) != 0);
   }
};

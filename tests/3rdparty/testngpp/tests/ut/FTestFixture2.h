
#ifndef __TESTNGPP_UT_FIXTURE_2_H
#define __TESTNGPP_UT_FIXTURE_2_H

#include <string>

#include <testngpp/TestFixture.h>

#include <testngpp/internal/TestCase.h>
#include <testngpp/internal/TestSuiteDesc.h>
#include <testngpp/internal/TestFixtureDesc.h>

#include "MyTestCase.h"

USING_MOCKCPP_NS
USING_TESTNGPP_NS

struct FTestFixture2
{
   TestFixtureDesc* fixtureDesc[2];

   TestCase* testCases[2][10];

   TestSuiteDesc* suiteDesc;

   TestFixture fixture;

   void setUp()
   {
     
      size_t size = sizeof(testCases[0])/sizeof(testCases[0][0]);

      testCases[0][0] = new MyTestCase("testCase0", "TestNothing0", 0, "TestNothing0.h", 1);
      testCases[0][1] = new MyTestCase("testCase1", "TestNothing0", 0, "TestNothing0.h", 11);

      testCases[0][2] = new MyTestCase("testCase2", "TestNothing0", testCases[0][0], "TestNothing0.h", 15);
      testCases[0][3] = new MyTestCase("testCase2", "TestNothing0", testCases[0][0], "TestNothing0.h", 15);
      testCases[0][4] = new MyTestCase("testCase2", "TestNothing0", testCases[0][0], "TestNothing0.h", 15);

      testCases[0][5] = new MyTestCase("testCase2", "TestNothing0", testCases[0][3], "TestNothing0.h", 15);
      testCases[0][6] = new MyTestCase("testCase2", "TestNothing0", testCases[0][3], "TestNothing0.h", 15);
      testCases[0][7] = new MyTestCase("testCase2", "TestNothing0", testCases[0][3], "TestNothing0.h", 15);
      testCases[0][8] = new MyTestCase("testCase2", "TestNothing0", testCases[0][7], "TestNothing0.h", 15);
      testCases[0][9] = new MyTestCase("testCase2", "TestNothing0", testCases[0][7], "TestNothing0.h", 15);

      testCases[1][0] = new MyTestCase("testCase0", "TestNothing1", "TestNothing1.h", 1);
      testCases[1][1] = new MyTestCase("testCase1", "TestNothing1", "TestNothing1.h", 11);
      testCases[1][2] = new MyTestCase("testCase2", "TestNothing1", "TestNothing1.h", 18);
      testCases[1][3] = new MyTestCase("testCase3", "TestNothing1", "TestNothing1.h", 21);
      testCases[1][4] = new MyTestCase("testCase4", "TestNothing1", "TestNothing1.h", 31);
      testCases[1][5] = new MyTestCase("testCase5", "TestNothing1", "TestNothing1.h", 41);
      testCases[1][6] = new MyTestCase("testCase6", "TestNothing1", "TestNothing1.h", 51);
      testCases[1][7] = new MyTestCase("testCase7", "TestNothing1", "TestNothing1.h", 61);
      testCases[1][8] = new MyTestCase("testCase8", "TestNothing1", "TestNothing1.h", 71);
      testCases[1][9] = new MyTestCase("testCase9", "TestNothing1", "TestNothing1.h", 81);

      fixtureDesc[0] = new TestFixtureDesc("TestNothing0" , "TestNothing0.h", testCases[0] , size);
      fixtureDesc[1] = new TestFixtureDesc("TestNothing1" , "TestNothing1.h", testCases[1] , size);

      suiteDesc = new TestSuiteDesc("TestNothingSuite", fixtureDesc, 2);
   }

   void tearDown()
   {
      size_t size = sizeof(testCases[0])/sizeof(testCases[0][0]);

      for(unsigned int i = 0; i < size; i++)
      {
         delete testCases[0][i];
         delete testCases[1][i];
      }

      delete fixtureDesc[0];
      delete fixtureDesc[1];

      delete suiteDesc;
   }

};

#endif

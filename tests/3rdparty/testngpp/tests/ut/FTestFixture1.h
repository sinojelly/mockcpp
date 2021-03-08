
#ifndef __FIXTURE_TEST_FIXTURE1_H__
#define __FIXTURE_TEST_FIXTURE1_H___

#include <testngpp/TestFixture.h>

#include <testngpp/internal/TestCase.h>
#include <testngpp/internal/TestFixtureDesc.h>
#include <testngpp/listener/TestCaseResultCollector.h>
#include <testngpp/runner/SimpleTestCaseRunner.h>


USING_MOCKCPP_NS
USING_TESTNGPP_NS

class FTestFixture1
{
   struct MyTestCase : public TESTNGPP_NS::TestCase
   {
      MyTestCase(TESTNGPP_NS::TestFixture* fixture
           , const std::string& nameOfCase
           , const std::string& nameOfFixture
           , const std::string& file
           , unsigned int line)
           : m_fixture(fixture)
           , TESTNGPP_NS::TestCase(nameOfCase, nameOfFixture, "mysuite", 0, file, line)
      {}

      TESTNGPP_NS::TestFixture* getFixture() const { return m_fixture; }
      void setFixture(TESTNGPP_NS::TestFixture* fixture) { }
      void runTest() {}

      TESTNGPP_NS::TestFixture* m_fixture;
   };

public:

   TESTNGPP_NS::TestFixtureDesc* desc;
   TESTNGPP_NS::TestCase* testcase[1];

   MockObject<TESTNGPP_NS::TestFixture> fixture;
   MockObject<TESTNGPP_NS::TestCaseResultCollector> collector;

public:

   void setUp()
   {
		testcase[0] = new MyTestCase(fixture, "testCase1", "TestNothing", "TestNothing.h", 11);
      desc = new TestFixtureDesc("TestNothing", "TestNothing.h", testcase, 1);
   }

   void tearDown()
   {
      delete testcase[0];
      delete desc;

      fixture.reset();
      collector.reset();
   }

   void verify()
   {
      fixture.verify();
      collector.verify();
   }
};

#endif


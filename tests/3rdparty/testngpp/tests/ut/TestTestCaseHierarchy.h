

#include <iostream>
#include <list>
#include <algorithm>

#include <cxxtest/TestSuite.h>

#include <mockcpp/mockcpp.hpp>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/internal/TestCase.h>

#include <testngpp/runner/TestCaseContainer.h>
#include <testngpp/runner/TestCaseFilter.h>

#include <testngpp/runner/TestCaseHierarchy.h>

#include "FTestFixture2.h"

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestTestCaseHierarchy: public CxxTest::TestSuite
{

   struct MyTestContainer : public TestCaseContainer
   {
      void addTestCase(const TestCase* testcase, bool userSpecified)
      { testcases.push_back(ValueType(testcase, userSpecified)); }

      typedef std::pair<const TestCase*, bool> ValueType;

      std::list<ValueType> testcases;

      typedef std::list<ValueType>::iterator iterator;

      bool exists(const TestCase* testcase, bool userSpecified = true)
      {
         iterator i = testcases.begin();
         for(; i != testcases.end(); i++)
         {
            if((*i).first == testcase && userSpecified == (*i).second)
               return true;
         }
         return false;
      }

   };

private:

   TESTNGPPST_RCP checkpoint;

   FTestFixture2 f;
   
   TestCaseHierarchy* hierarchy;

   MockObject<TestCaseFilter> filter;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      f.setUp();

      MOCK_METHOD(filter, isCaseMatch)
         .defaults()
         .will(returnValue(true));

      MOCK_METHOD(filter, isCaseMatch)
        .stubs()
        .with(eq((const TestCase*)f.testCases[0][0]))
        .will(returnValue(false));


      hierarchy = new TestCaseHierarchy (f.fixtureDesc[0], filter);

   }
   void tearDown()
   {
      delete hierarchy;

      filter.verify();

      filter.reset();

      f.tearDown();

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }


   void test_should_be_able_to_get_direct_successors_of_root(void)
   {
      MyTestContainer container;

      hierarchy->getDirectSuccessors(0, &container);

      TS_ASSERT_EQUALS(2, container.testcases.size());

      MyTestContainer::iterator iter = container.testcases.begin();
      TS_ASSERT(container.exists(f.testCases[0][0], false));
      TS_ASSERT(container.exists(f.testCases[0][1], true));
   }

   void test_should_be_able_to_get_direct_successors(void)
   {
      MyTestContainer container;

      hierarchy->getDirectSuccessors(f.testCases[0][0], &container);

      TS_ASSERT_EQUALS(3, container.testcases.size());

      for(unsigned int i=0; i < 3 ; i++)
      {
         TS_ASSERT(container.exists(f.testCases[0][i+2]));
      }
   }

   void test_should_be_able_to_get_all_successors_of_root(void)
   {
      MyTestContainer container;

      hierarchy->getSuccessors(0, &container);
      TS_ASSERT_EQUALS(10, container.testcases.size());

      TS_ASSERT(container.exists(f.testCases[0][0], false));

      for(unsigned int i=1; i < 10 ; i++)
      {
         TS_ASSERT(container.exists(f.testCases[0][i]));
      }
      
   }

   void test_should_be_able_to_get_all_successors(void)
   {
      MyTestContainer container;

      hierarchy->getSuccessors(f.testCases[0][0], &container);
      TS_ASSERT_EQUALS(8, container.testcases.size());

      for(unsigned int i=0; i < 8 ; i++)
      {
         TS_ASSERT(container.exists(f.testCases[0][i+2]));
      }
   }
};

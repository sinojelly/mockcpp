
#include <cxxtest/TestSuite.h> 
#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/internal/AssertionFailure.h>


using namespace testngpp;

class TestAssertionFailure: public CxxTest::TestSuite
{
private:
   TESTNGPPST_RCP checkpoint;

   TESTNGPP_NS::AssertionFailure* failure;
   
public:
   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
      failure = new AssertionFailure("TestNothing.h", 23, "AssertionFailed");
   }

   void tearDown()
   {
      delete failure;
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToGetFileName()
   {
      TS_ASSERT_EQUALS(std::string("TestNothing.h"), failure->getFileName());
   }

   void testShouldBeAbleToGetLineOfFile()
   {
      TS_ASSERT_EQUALS((unsigned int)23, failure->getLineOfFile());
   }

   void testShouldBeAbleToGetTheReasonOfFailure()
   {
      TS_ASSERT_EQUALS(std::string("AssertionFailed"), failure->what());
   }
};

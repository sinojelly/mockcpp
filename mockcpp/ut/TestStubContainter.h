
#include <cxxtest/TestSuite.h>
#include <mockcpp/StubContainer.h>
#include <mockcpp/Any.h>
#include <mockcpp/MemoryCheckPoint.h>

USING_MOCKCPP_NS

class TestStubContainer : public CxxTest::TestSuite
{
   struct TestStub : public Stub
   {
       TestStub(unsigned int maxTimes) 
         : times(0), limit(maxTimes) {}

       bool isCompleted() const
       { return times >= limit; }

       Any& invoke(const Invocation& inv)
       { times++; return any; }
    
       std::string toString() const
       { return ""; }

   private:

       Any any;
       unsigned int times;
       unsigned int limit;
   };

private:

   MemoryCheckPoint checkpoint;

public:

   void setUp()
   {
      checkpoint = mockcppSetCheckPoint();

   }
   void tearDown()
   {
      MOCKCPP_CHECK_POINT_VERIFY(checkpoint);
   }


	/////////////////////////////////////////////////////////

	void testShouldBeAbleToGetAddedStub()
	{
       StubContainer container("");
       Invocation inv("", 0, 1);

       Stub* stub0 = new TestStub(1);
       Stub* stub1 = new TestStub(1);

       container.addStub(stub0);
       container.addStub(stub1);
       
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);
       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);
   }

	void testShouldAlwaysReturnAStubBeforeItIsCompleted()
	{
       StubContainer container("");
       Invocation inv("", 0, 1);

       Stub* stub0 = new TestStub(3);
       Stub* stub1 = new TestStub(1);

       container.addStub(stub0);
       container.addStub(stub1);
       
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);
   }

	void testShouldAlwaysReturnLastStubIfAllStubsHaveBeenReturnedEvenIfItHasBeenCompleted()
	{
       StubContainer container("");
       Invocation inv("", 0, 1);

       Stub* stub0 = new TestStub(1);
       Stub* stub1 = new TestStub(1);

       container.addStub(stub0);
       container.addStub(stub1);
       
       TS_ASSERT_EQUALS(container.getStub(), stub0);
       stub0->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);

       TS_ASSERT_EQUALS(container.getStub(), stub1);
       stub1->invoke(inv);
   }

   void testShouldReturnNullIfNoStubWasAdded()
   {
       StubContainer container("");
       
       TS_ASSERT(container.getStub() == 0);
   }
};


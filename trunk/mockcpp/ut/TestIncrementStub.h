
#include <cxxtest/TestSuite.h>

#include <IncrementStub.h>

USING_MOCKCPP_NS

class TestIncrementStub: public CxxTest::TestSuite
{
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

   void testShouldBeAbleIncreaseFromStartValue()
   {
      IncrementStub<int> stub(5);

      TS_ASSERT_EQUALS(5, any_cast<int>(stub.invoke()));
      TS_ASSERT_EQUALS(6, any_cast<int>(stub.invoke()));
      TS_ASSERT_EQUALS(7, any_cast<int>(stub.invoke()));
      TS_ASSERT_EQUALS(8, any_cast<int>(stub.invoke()));
   }

   void testShouldThrowExceptionAfterReachingItsEndValue()
   {
      IncrementStub<int> stub(5,7);

      TS_ASSERT_EQUALS(5, any_cast<int>(stub.invoke()));
      TS_ASSERT_EQUALS(6, any_cast<int>(stub.invoke()));
      TS_ASSERT_EQUALS(7, any_cast<int>(stub.invoke()));
      TS_ASSERT_THROWS(any_cast<int>(stub.invoke()), Exception);
      TS_ASSERT_THROWS(any_cast<int>(stub.invoke()), Exception);
   }
};

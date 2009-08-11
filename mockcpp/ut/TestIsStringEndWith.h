
#include <cxxtest/TestSuite.h>
#include <MemoryCheckPoint.h>
#include <IsStringEndWith.h>

USING_MOCKCPP_NS

class TestIsStringEndWith: public CxxTest::TestSuite
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


	/////////////////////////////////////////////////////////

	void testShouldReturnTrueIfTheParameterDoesEndWithSpecifiedString()
	{
       IsStringEndWith predict;

       std::string input("efgabcd");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnFalseIfTheParameterDoesNotEndWithSpecifiedString()
	{
       IsStringEndWith predict;

       std::string input("efagbcd");
       std::string target("abcd");

       TS_ASSERT(!predict.predict(input, target));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringEndWith predict;

       TS_ASSERT_EQUALS(std::string("endWith(\"abcd\")"), predict.toString("abcd"));
	}
};


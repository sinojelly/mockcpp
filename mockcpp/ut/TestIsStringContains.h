
#include <cxxtest/TestSuite.h>
#include <mockcpp/MemoryCheckPoint.h>
#include <mockcpp/IsStringContains.h>

USING_MOCKCPP_NS

class TestIsStringContains: public CxxTest::TestSuite
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

	void testShouldReturnTrueIfTheInputDoesContainsSpecifiedString()
	{
       IsStringContains predict;

       std::string input("efgabcd12");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnTrueIfTheInputStartWithSpecifiedString()
	{
       IsStringContains predict;

       std::string input("gabcd12");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnTrueIfTheInputEndWithSpecifiedString()
	{
       IsStringContains predict;

       std::string input("g12abcd");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnTrueIfTheInputEqualsSpecifiedString()
	{
       IsStringContains predict;

       std::string input("abcd");
       std::string target("abcd");

       TS_ASSERT(predict.predict(input, target));
	}

	void testShouldReturnFalseIfTheInputDoesNotContainsSpecifiedString()
	{
       IsStringContains predict;

       std::string input("efgafbcd12");
       std::string target("abcd");

       TS_ASSERT(!predict.predict(input, target));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringContains predict;

       TS_ASSERT_EQUALS(std::string("contains(\"abcd\")"), predict.toString("abcd"));
	}
};


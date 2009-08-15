
#include <cxxtest/TestSuite.h>

#include <mockcpp/MemoryCheckPoint.h>

#include <mockcpp/IsStringStartWith.h>

USING_MOCKCPP_NS

class TestIsStringStartWith: public CxxTest::TestSuite
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

	void testShouldReturnTrueIfTheParameterDoesStartWithSpecifiedString()
	{
       IsStringStartWith constraint;

       std::string input("abcdefg");
       std::string target("abcd");

       TS_ASSERT(constraint.predict(input, target));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedString()
	{
       IsStringStartWith constraint;

       std::string input("abcfefg");
       std::string target("abcd");

       TS_ASSERT(!constraint.predict(input, target));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringStartWith constraint;

       TS_ASSERT_EQUALS(std::string("startWith(\"abcd\")"), constraint.toString("abcd"));
	}
};


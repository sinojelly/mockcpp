
#include <cxxtest/TestSuite.h>

#include <MemoryCheckPoint.h>

#include <IsStringStartWith.h>

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
       IsStringStartWith constraint("abcd");

       std::string s("abcdefg");

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedString()
	{
       IsStringStartWith constraint("abcd");

       std::string s("abcfefg");

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesStartWithSpecifiedPChar()
	{
       IsStringStartWith constraint("abcd");

       char* s = (char*)"abcdefg";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedPChar()
	{
       IsStringStartWith constraint("abcd");

       char* s = (char*)"abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesStartWithSpecifiedPUChar()
	{
       IsStringStartWith constraint("abcd");

       unsigned char* s = (unsigned char*)"abcdefg";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedPUChar()
	{
       IsStringStartWith constraint("abcd");

       unsigned char* s = (unsigned char*)"abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesStartWithSpecifiedConstPChar()
	{
       IsStringStartWith constraint("abcd");

       const char* s = "abcdefg";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedConstPChar()
	{
       IsStringStartWith constraint("abcd");

       const char* s = "abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesStartWithSpecifiedConstPUChar()
	{
       IsStringStartWith constraint("abcd");

       unsigned const char* s = (unsigned const char*)"abcdefg";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotStartWithSpecifiedConstPUChar()
	{
       IsStringStartWith constraint("abcd");

       unsigned const char* s = (const unsigned char*)"abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterIsAnNullPointer()
	{
       IsStringStartWith constraint("abcd");

       const char* s = 0;

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringStartWith constraint("abcd");

       TS_ASSERT_EQUALS(std::string("startWith(\"abcd\")"), constraint.toString());
	}
};


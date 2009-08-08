
#include <cxxtest/TestSuite.h>
#include <MemoryCheckPoint.h>
#include <IsStringContains.h>

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

	void testShouldReturnTrueIfTheParameterDoesContainsSpecifiedString()
	{
       IsStringContains constraint("abcd");

       std::string s("1abcdef");

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotContainsSpecifiedString()
	{
       IsStringContains constraint("abcd");

       std::string s("1abcfefg");

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesContainsSpecifiedPChar()
	{
       IsStringContains constraint("abcd");

       char* s = "1abcdefg";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotContainsSpecifiedPChar()
	{
       IsStringContains constraint("abcd");

       char* s = "1abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesContainsSpecifiedPUChar()
	{
       IsStringContains constraint("abcd");

       unsigned char* s = (unsigned char*)"1abcdefg";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotContainsSpecifiedPUChar()
	{
       IsStringContains constraint("abcd");

       unsigned char* s = (unsigned char*)"1abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesContainsSpecifiedConstPChar()
	{
       IsStringContains constraint("abcd");

       const char* s = "123abcd";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotContainsSpecifiedConstPChar()
	{
       IsStringContains constraint("abcd");

       const char* s = "12abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesContainsSpecifiedConstPUChar()
	{
       IsStringContains constraint("abcd");

       unsigned const char* s = (unsigned const char*)"123abcd";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotContainsSpecifiedConstPUChar()
	{
       IsStringContains constraint("abcd");

       unsigned const char* s = (unsigned const char*)"12abccefg";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterIsAnNullPointer()
	{
       IsStringContains constraint("abcd");

       const char* s = 0;

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringContains constraint("abcd");

       TS_ASSERT_EQUALS(std::string("contains(\"abcd\")"), constraint.toString());
	}
};


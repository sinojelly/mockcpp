
#include <cxxtest/TestSuite.h>
#include <Any.h>
#include <IsStringEndWith.h>

using namespace mockcpp;

class TestIsStringEndWith: public CxxTest::TestSuite
{
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldReturnTrueIfTheParameterDoesEndWithSpecifiedString()
	{
       IsStringEndWith constraint("abcd");

       std::string s("efgabcd");

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotEndWithSpecifiedString()
	{
       IsStringEndWith constraint("abcd");

       std::string s("efgabcf");

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesEndWithSpecifiedPChar()
	{
       IsStringEndWith constraint("abcd");

       char* s = "efgabcd";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotEndWithSpecifiedPChar()
	{
       IsStringEndWith constraint("abcd");

       char* s = "efgabcc";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesEndWithSpecifiedPUChar()
	{
       IsStringEndWith constraint("abcd");

       unsigned char* s = (unsigned char*)"efgabcd";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotEndWithSpecifiedPUChar()
	{
       IsStringEndWith constraint("abcd");

       unsigned char* s = (unsigned char*)"efgabcc";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesEndWithSpecifiedConstPChar()
	{
       IsStringEndWith constraint("abcd");

       const char* s = "abcd";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotEndWithSpecifiedConstPChar()
	{
       IsStringEndWith constraint("abcd");

       const char* s = "efgabcc";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnTrueIfTheParameterDoesEndWithSpecifiedConstPUChar()
	{
       IsStringEndWith constraint("abcd");

       unsigned const char* s = (unsigned const char*)"abcd";

       TS_ASSERT(constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterDoesNotEndWithSpecifiedConstPUChar()
	{
       IsStringEndWith constraint("abcd");

       unsigned const char* s = (unsigned const char*)"efgabcc";

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldReturnFalseIfTheParameterIsAnNullPointer()
	{
       IsStringEndWith constraint("abcd");

       const char* s = 0;

       TS_ASSERT(!constraint.eval(s));
	}

	void testShouldBeAbleConvertToRequiredFormattedString()
	{
       IsStringEndWith constraint("abcd");

       TS_ASSERT_EQUALS(std::string("endWith(\"abcd\")"), constraint.toString());
	}
};


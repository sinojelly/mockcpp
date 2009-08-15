
#include <cxxtest/TestSuite.h>
#include <mockcpp/Invocation.h>
#include <mockcpp/Any.h>

USING_MOCKCPP_NS

class TestInvocation: public CxxTest::TestSuite
{
public:

	/////////////////////////////////////////////////////////

	void testShouldBeAbleToPassAnyNumberOfParametersWithLimitOfConstructorParameterNumber()
	{
		Invocation inv(__FUNCTION__,1,2,3);

		TS_ASSERT(any_cast<int>(inv.getParameter(1)) == 1);
		TS_ASSERT(any_cast<int>(inv.getParameter(2)) == 2);
		TS_ASSERT(any_cast<int>(inv.getParameter(3)) == 3);

		TS_ASSERT(inv.getParameter(4).empty());
		TS_ASSERT(inv.getParameter(5).empty());
		TS_ASSERT(inv.getParameter(6).empty());
	}

	void testShouldBeAbleToGetAllInputParameters()
	{
		Invocation inv(__FUNCTION__, 1,2,3,4,5,6);

		TS_ASSERT(any_cast<int>(inv.getParameter(1)) == 1);
		TS_ASSERT(any_cast<int>(inv.getParameter(2)) == 2);
		TS_ASSERT(any_cast<int>(inv.getParameter(3)) == 3);
		TS_ASSERT(any_cast<int>(inv.getParameter(4)) == 4);
		TS_ASSERT(any_cast<int>(inv.getParameter(5)) == 5);
		TS_ASSERT(any_cast<int>(inv.getParameter(6)) == 6);
	}

	void testShouldEqualsDefaultAnyInstanceIfTryToGetThe0thParameter()
	{
		Invocation inv(__FUNCTION__, 1,2,3,4,5,6);
		TS_ASSERT(inv.getParameter(0).empty());
	}

	void testShouldEqualsDefaultAnyInstanceIfTryToGetTheNthParameterAndNIsGreaterThanNumberOfInputParameters()
	{
		Invocation inv(__FUNCTION__, 1,2,3,4,5,6);
		TS_ASSERT(inv.getParameter(7).empty());
	}
};



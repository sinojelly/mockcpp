
#include <cppunit/extensions/HelperMacros.h>
#include <Invocation.h>
#include <Any.h>

using namespace mockcpp;

class TestInvocation : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestInvocation );
	CPPUNIT_TEST( testShouldEqualsDefaultAnyInstanceIfTryToGetThe0thParameter );
	CPPUNIT_TEST( testShouldEqualsDefaultAnyInstanceIfTryToGetTheNthParameterAndNIsGreaterThanNumberOfInputParameters );
	CPPUNIT_TEST( testShouldBeAbleToGetAllInputParameters );
	CPPUNIT_TEST( testShouldBeAbleToPassAnyNumberOfParametersWithLimitOfConstructorParameterNumber );
	CPPUNIT_TEST_SUITE_END();

public:

	/////////////////////////////////////////////////////////

	void testShouldBeAbleToPassAnyNumberOfParametersWithLimitOfConstructorParameterNumber()
	{
		Invocation inv(1,2,3);

		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(1)) == 1);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(2)) == 2);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(3)) == 3);

		CPPUNIT_ASSERT(inv.getParameter(4).empty());
		CPPUNIT_ASSERT(inv.getParameter(5).empty());
		CPPUNIT_ASSERT(inv.getParameter(6).empty());
	}

	void testShouldBeAbleToGetAllInputParameters()
	{
		Invocation inv(1,2,3,4,5,6);

		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(1)) == 1);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(2)) == 2);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(3)) == 3);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(4)) == 4);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(5)) == 5);
		CPPUNIT_ASSERT(any_cast<int>(inv.getParameter(6)) == 6);
	}

	void testShouldEqualsDefaultAnyInstanceIfTryToGetThe0thParameter()
	{
		Invocation inv(1,2,3,4,5,6);
		CPPUNIT_ASSERT(inv.getParameter(0).empty());
	}

	void testShouldEqualsDefaultAnyInstanceIfTryToGetTheNthParameterAndNIsGreaterThanNumberOfInputParameters()
	{
		Invocation inv(1,2,3,4,5,6);
		CPPUNIT_ASSERT(inv.getParameter(7).empty());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestInvocation );





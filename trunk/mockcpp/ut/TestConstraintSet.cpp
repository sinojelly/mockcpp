
#include <cppunit/extensions/HelperMacros.h>
#include <Any.h>
#include <IsEqual.h>
#include <ConstraintSet.h>
#include <ChainingMockHelper.h>
#include <Invocation.h>

using namespace mockcpp;

class TestConstraintSet : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestConstraintSet );
	CPPUNIT_TEST( testShouldMatchCorrespondingInvocation );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldMatchCorrespondingInvocation()
	{
		ConstraintSet cs(eq(1), eq(2));
		Invocation inv(1, 2);

		CPPUNIT_ASSERT(cs.matches(inv));
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestConstraintSet );

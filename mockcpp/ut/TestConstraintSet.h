
#include <cxxtest/TestSuite.h>

#include <Any.h>
#include <IsEqual.h>
#include <ConstraintSet.h>
#include <ChainingMockHelper.h>
#include <Invocation.h>

USING_MOCKCPP_NS

class TestConstraintSet : public CxxTest::TestSuite
{
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldMatchCorrespondingInvocation()
	{
		ConstraintSet cs(eq(1), eq(2));
		Invocation inv(__FUNCTION__, 1, 2);

		TS_ASSERT(cs.matches(inv));
	}

};


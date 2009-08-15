
#include <cxxtest/TestSuite.h>

#include <mockcpp/Any.h>
#include <mockcpp/IsEqual.h>
#include <mockcpp/ConstraintSet.h>
#include <mockcpp/ChainingMockHelper.h>
#include <mockcpp/Invocation.h>

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


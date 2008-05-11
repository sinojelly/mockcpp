
#include <cppunit/extensions/HelperMacros.h>
#include <InvocationMocker.h>
#include <Invocation.h>
#include <Namespace.h>
#include <InvocationMockBuilder.h>
#include <ChainableMockMethodCore.h>
#include <ChainingMockHelper.h>
#include <ConstraintSet.h>
#include <InvokedTimesRecorder.h>

using namespace mockcpp;


class TestChainableMockMethodCore : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestChainableMockMethodCore );
	CPPUNIT_TEST( testShouldReturnTheStubOfMatchedInvocationMocker );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldReturnTheStubOfMatchedInvocationMocker()
	{
		InvocationMocker* mocker = new InvocationMocker(0);
		mocker->setStub(returnValue(8));
		mocker->addMatcher(once());
		ChainableMockMethodCore core("foo", 0);
		core.addInvocationMocker(mocker);

      SelfDescribe* resultProvider = 0;
		CPPUNIT_ASSERT(8 == any_cast<int>(core.invoke(Invocation(), resultProvider)));
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestChainableMockMethodCore );

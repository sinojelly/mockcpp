
#include <cppunit/extensions/HelperMacros.h>
#include <InvocationMocker.h>
#include <Invocation.h>
#include <Namespace.h>
#include <InvocationMockBuilder.h>
#include <ChainableMockMethodCore.h>
#include <ChainingMockHelper.h>
#include <ConstraintSet.h>

using namespace mockcpp;


class TestChainableMockMethodCore : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestChainableMockMethodCore );
	CPPUNIT_TEST( testShouldReturnTheStubOfMatchedInvocationMocker );
	CPPUNIT_TEST( testShouldReturnDefaultStubIfThereIsNoMatchedInvocationMocker );
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

		CPPUNIT_ASSERT(8 == any_cast<int>(core.invoke(Invocation())));
	}

	void testShouldReturnDefaultStubIfThereIsNoMatchedInvocationMocker()
   {
		InvocationMocker* mocker = new InvocationMocker(0);
		mocker->setStub(returnValue(8));
		mocker->addMatcher(new ConstraintSet(eq(10)));
		ChainableMockMethodCore core("foo", 0);
		core.addInvocationMocker(mocker);
		core.setDefaultStub(returnValue(3));

		CPPUNIT_ASSERT(3 == any_cast<int>(core.invoke(Invocation())));
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestChainableMockMethodCore );

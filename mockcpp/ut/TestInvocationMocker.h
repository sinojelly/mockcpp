
#include <cxxtest/TestSuite.h>
#include <InvocationMocker.h>
#include <Invocation.h>
#include <InvocationMockBuilder.h>
#include <ChainingMockHelper.h>
#include <Any.h>
#include <InvokedTimesRecorder.h>

using namespace mockcpp;

class TestInvocationMocker : public CxxTest::TestSuite
{
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldReturnSettedStubWhenCallingInvoke()
	{
		InvocationMocker mocker(0);
		Invocation inv(__FUNCTION__);

		mocker.setStub(returnValue(10));

		TS_ASSERT(10 == any_cast<int>(mocker.invoke(inv)));
	}

	void testShouldSetInvokedStateAfterItsInvoked()
	{
		InvocationMocker mocker(0);
		Invocation inv(__FUNCTION__);

		TS_ASSERT(!mocker.hasBeenInvoked());
		mocker.invoke(inv);
		TS_ASSERT(mocker.hasBeenInvoked());
	}

};



#include <cxxtest/TestSuite.h>

#include <Any.h>
#include <ChainableMockObject.h>
#include <Namespace.h>
#include <InvocationMockBuilder.h>
#include <ChainingMockHelper.h>

using namespace mockcpp;

class TestChainableObject2 : public CxxTest::TestSuite
{
	class Foo : public ChainableMockObject
	{
	public:
		Foo(Namespace* ns = 0)
			: ChainableMockObject("Foo", ns)
		{}

		int foo(int& i, unsigned long j)
		{
			return invoke<int>("foo")("foo", i, j);
		}
	};
public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldNotGetSameCoreMockerWithDifferentName()
	{
		ChainableMockObject obj("obj");
		TS_ASSERT(obj.getMethod("foo") != obj.getMethod("fo"));
		obj.verify();
	}

	void testShouldAlwaysGetSameCoreMockerWithSameName()
	{
		ChainableMockObject obj("obj");
		TS_ASSERT_EQUALS(obj.getMethod("foo"), obj.getMethod("foo"));
		obj.verify();
	}

	void testShouldReturnDefaultStubIfThereIsNotMatchedExpectation()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(10, foo.foo(i, 3));
		TS_ASSERT_EQUALS(10, foo.foo(i, 4));

		foo.verify();
	}

	void testShouldReturnDefaultStubIfThereIsNotMatchedExpectation2()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
		   .will(returnValue(10));

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(5));
		
		int i = 1;

		TS_ASSERT_EQUALS(5 , foo.foo(i, 2));
		TS_ASSERT_EQUALS(10, foo.foo(i, 3));
		TS_ASSERT_EQUALS(10, foo.foo(i, 4));

		foo.verify();
	}

	void testShouldReturnTheValueOfSettedStubByWill()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldReturnTheValueOfSettedStubByWillIfParameterMatchesConstraintsSpecifiedByWith()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldReturnDefaultValueIfExpectionMismatch()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
		   .will(returnValue(0));

		foo.method("foo")
		   .stubs()
		   .with(eq(2), eq((unsigned char)3))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_EQUALS(0, foo.foo(i, 3));

		foo.verify();
	}

	void testShouldReturnDefaultValueIfExpectionMismatch2()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
		   .will(returnValue(0));

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(0, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldReturnTheDefaultValueOfSpecifiedTypeIfExistingExpectationDoesNotMatch()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
		   .will(returnValue(0));

		foo.method("foo")
		   .expects(once())
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		TS_ASSERT_EQUALS(0, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldRaiseExceptionIfAInvokedWasExpectedNever()
	{
		Foo foo;

		foo.method("foo")
		   .expects(never())
		   .will(returnValue(10));

		int i = 1;
    
		TS_ASSERT_THROWS(foo.foo(i, 2), mockcpp::Exception);

		foo.verify();
	}

	void testShouldBeAbleToOutBoundParameter()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(outBound(3), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(3, i);

		foo.verify();
	}

	void testShouldBeAbleToOutBoundParameterAndAttachOtherConstraint()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(outBound(3, eq(1)), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 1;

 		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(3, i);

		foo.verify();
	}

	void testShouldFailWhenOutBoundParameterAndAttachAMismatchedConstraint()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(outBound(3, eq(2)), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 1;

		TS_ASSERT_THROWS(foo.foo(i, 2), mockcpp::Exception);
		//TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		TS_ASSERT_THROWS(foo.verify(), mockcpp::Exception);
	}

	void testShouldBeAbleToSupportAtLeast()
	{
		Foo foo;

		foo.method("foo")
		   .expects(atLeast(1))
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldFailIfThereIsNoMatchingInvocationButTheExpectWasSetAsAtLeaseOnce()
	{
		Foo foo;

		foo.method("foo")
		   .expects(atLeast(1))
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		TS_ASSERT_THROWS(foo.verify(), mockcpp::Exception);
	}

	void testShouldFailIfInvokedTimeExceedsTheLimitationByAtMost()
	{
		Foo foo;

		foo.method("foo")
		   .expects(atMost(2))
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_THROWS(foo.foo(i,2), mockcpp::Exception);
		TS_ASSERT_THROWS(foo.foo(i,2), mockcpp::Exception);

		foo.verify();
	}

	void testShouldFailIfInvokedTimesIsLessThanExpectedTimes()
	{
		Foo foo;

		foo.method("foo")
		   .expects(exactly(2))
		   .with(eq(1), eq((unsigned long)4))
		   .will(returnValue(3));

		foo.method("foo")
		   .expects(exactly(2))
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		TS_ASSERT_THROWS(foo.verify(), mockcpp::Exception);
	}

	void testShouldFailIfInvokedTimesIsMoreThanExpectedTimes()
	{
		Foo foo;

		foo.method("foo")
		   .expects(exactly(2))
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(10, foo.foo(i, 2));

		TS_ASSERT_THROWS(foo.foo(i,2), mockcpp::Exception);

		foo.verify();
   }
};


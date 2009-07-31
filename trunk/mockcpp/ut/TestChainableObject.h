
#include <cxxtest/TestSuite.h>
#include <Any.h>
#include <ChainableMockObject.h>
#include <InvocationMockBuilder.h>
#include <ChainingMockHelper.h>

using namespace mockcpp;



class TestChainableObject : public CxxTest::TestSuite
{
	class Foo : public ChainableMockObject
	{
	public:
		Foo()
			: ChainableMockObject("Foo")
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
	void testShouldSupportOrderingExpectationByAfter()
	{
		Foo foo ;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
		   .id("1");

		foo.method("foo")
		   .expects(once())
		   .with(eq(2), eq((unsigned long)2))
		   .after("1")
		   .will(returnValue(12));

		int i = 2, j = 1;

		TS_ASSERT_EQUALS(10, foo.foo(j, 2));
		TS_ASSERT_EQUALS(12, foo.foo(i, 2));

		foo.verify();
	}

	void testShouldSupportOrderingExpectationByBefore()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .before("1")
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
		   .id("1");

		int i = 2, j = 1;

		TS_ASSERT_EQUALS(10, foo.foo(i, 2));
		TS_ASSERT_EQUALS(10, foo.foo(j, 2));

		foo.verify();
	}

	void testShouldFailIfInvocationOutOfOrder()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
		   .id("1");

		foo.method("foo")
		   .expects(once())
		   .before("1")
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2, j = 1;

		TS_ASSERT_EQUALS(10, foo.foo(j, 2));

		TS_ASSERT_THROWS(foo.foo(i,2), mockcpp::Exception);

		foo.verify();
	}

	void testShouldFailIfInvocationOutOfOrder2()
	{
		Foo foo;

		foo.method("foo")
	   	   .expects(once())
	   	   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue(10))
            .id("1");

		foo.method("foo")
		   .expects(once())
		   .with(eq(2), eq((unsigned long)2))
		   .after("1")
		   .will(returnValue(10));

		int i = 2, j = 1;

		TS_ASSERT_THROWS(foo.foo(i, 2), mockcpp::Exception);
		TS_ASSERT_EQUALS(10, foo.foo(j, 2));

		foo.verify();
	}

	void testShouldFailIfReturnedTypeDoesNotMatchRequiredType2()
	{
		Foo foo;

		foo.method("foo")
		   .defaults()
	  	   .will(returnValue((long)10));

		int i = 2;

		TS_ASSERT_THROWS(foo.foo(i, 2), mockcpp::Exception);

		foo.verify();
	}

	void testShouldFailIfReturnedTypeDoesNotMatchRequiredType()
	{
		Foo foo;

		foo.method("foo")
		   .expects(once())
		   .with(eq(1), eq((unsigned long)2))
		   .will(returnValue((long)10));

		int i = 1;

		TS_ASSERT_THROWS(foo.foo(i,2), mockcpp::Exception);

		foo.verify();
	}

	void testShouldFailIfInvokedTimesIsMoreThanExpectedTimes()
	{
		Foo foo;

		foo.method("foo")
		   .expects(never())
		   .with(eq(2), eq((unsigned long)2))
		   .will(returnValue(10));

		int i = 2;

		TS_ASSERT_THROWS(foo.foo(i,2), mockcpp::Exception);

		foo.verify();
	}
};


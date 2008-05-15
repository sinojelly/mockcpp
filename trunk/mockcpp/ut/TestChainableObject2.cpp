
#include <cppunit/extensions/HelperMacros.h>
#include <Any.h>
#include <ChainableMockObject.h>
#include <Namespace.h>
#include <InvocationMockBuilder.h>
#include <ChainingMockHelper.h>

using namespace mockcpp;

class Foo : public ChainableMockObject
{
public:
	Foo(Namespace* ns = 0)
		: ChainableMockObject("Foo", ns)
	{}

	int foo(int& i, unsigned long j)
	{
		return invoke<int>("foo")(i, j);
	}
};

class TestChainableObject2 : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestChainableObject2 );
	CPPUNIT_TEST( testShouldAlwaysGetSameCoreMockerWithSameName );
	CPPUNIT_TEST( testShouldNotGetSameCoreMockerWithDifferentName );
	CPPUNIT_TEST( testShouldReturnTheValueOfSettedStubByWill );
	CPPUNIT_TEST( testShouldReturnTheValueOfSettedStubByWillIfParameterMatchesConstraintsSpecifiedByWith );
	CPPUNIT_TEST( testShouldReturnTheDefaultValueOfSpecifiedTypeIfExistingExpectationDoesNotMatch );
	CPPUNIT_TEST( testShouldReturnDefaultValueIfExpectionMismatch );
	CPPUNIT_TEST( testShouldReturnDefaultValueIfExpectionMismatch2 );
	CPPUNIT_TEST( testShouldReturnDefaultStubIfThereIsNotMatchedExpectation );
	CPPUNIT_TEST( testShouldReturnDefaultStubIfThereIsNotMatchedExpectation2 );
	CPPUNIT_TEST( testShouldBeAbleToOutBoundParameter );
	CPPUNIT_TEST( testShouldBeAbleToOutBoundParameterAndAttachOtherConstraint );
	CPPUNIT_TEST( testShouldBeAbleToSupportAtLeast );

	CPPUNIT_TEST_EXCEPTION( testShouldRaiseExceptionIfAInvokedWasExpectedNever, AssertionFailedError);
	CPPUNIT_TEST_EXCEPTION( testShouldFailWhenOutBoundParameterAndAttachAMismatchedConstraint, AssertionFailedError );
	CPPUNIT_TEST_EXCEPTION( testShouldFailIfThereIsNoMatchingInvocationButTheExpectWasSetAsAtLeaseOnce, AssertionFailedError );
	CPPUNIT_TEST_EXCEPTION( testShouldFailIfInvokedTimeExceedsTheLimitationByAtMost, AssertionFailedError );
	CPPUNIT_TEST_EXCEPTION( testShouldFailIfInvokedTimesIsMoreThanExpectedTimes, AssertionFailedError );
	CPPUNIT_TEST_EXCEPTION( testShouldFailIfInvokedTimesIsLessThanExpectedTimes, AssertionFailedError );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldNotGetSameCoreMockerWithDifferentName()
   {
		ChainableMockObject obj("obj");
      CPPUNIT_ASSERT(obj.getMethod("foo") != obj.getMethod("fo"));
      obj.verify();
   }

	void testShouldAlwaysGetSameCoreMockerWithSameName()
	{
		ChainableMockObject obj("obj");
      CPPUNIT_ASSERT_EQUAL(obj.getMethod("foo"), obj.getMethod("foo"));
      obj.verify();
	}

   void testShouldReturnDefaultStubIfThereIsNotMatchedExpectation()
   {
		Foo foo;

		foo.method("foo")
			.defaults()
         .will(returnValue(10));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 3));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 4));

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
      CPPUNIT_ASSERT_EQUAL(5 , foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 3));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 4));
		foo.verify();
	}

   void testShouldReturnTheValueOfSettedStubByWill()
   {
		Foo foo;

		foo.method("foo")
         .expects(once())
	      .will(returnValue(10));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
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
      CPPUNIT_ASSERT_EQUAL(0, foo.foo(i, 3));

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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(0, foo.foo(i, 2));
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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));

      CPPUNIT_ASSERT_EQUAL(0, foo.foo(i, 2));

		foo.verify();
   }

   void testShouldRaiseExceptionIfAInvokedWasExpectedNever()
   {
		Foo foo;

		foo.method("foo")
         .expects(never())
	      .will(returnValue(10));

		int i = 1;
    
		foo.foo(i, 2);
   }

	void testShouldBeAbleToOutBoundParameter()
   {
		Foo foo;

		foo.method("foo")
         .expects(once())
         .with(outBound(3), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(3, i);
   }

	void testShouldBeAbleToOutBoundParameterAndAttachOtherConstraint()
   {
		Foo foo;

		foo.method("foo")
         .expects(once())
         .with(outBound(3, eq(1)), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(3, i);
   }

	void testShouldFailWhenOutBoundParameterAndAttachAMismatchedConstraint()
   {
		Foo foo;

		foo.method("foo")
         .expects(once())
         .with(outBound(3, eq(2)), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }

	void testShouldBeAbleToSupportAtLeast()
   {
		Foo foo;

		foo.method("foo")
         .expects(atLeast(1))
         .with(eq(2), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }

	void testShouldFailIfThereIsNoMatchingInvocationButTheExpectWasSetAsAtLeaseOnce()
   {
		Foo foo;

		foo.method("foo")
         .expects(atLeast(1))
         .with(eq(2), eq((unsigned long)2))
	      .will(returnValue(10));

		foo.verify();
   }

	void testShouldFailIfInvokedTimeExceedsTheLimitationByAtMost()
   {
		Foo foo;

		foo.method("foo")
         .expects(atMost(2))
         .with(eq(2), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }

	void testShouldFailIfInvokedTimesIsMoreThanExpectedTimes()
   {
		Foo foo;

		foo.method("foo")
         .expects(exactly(2))
         .with(eq(2), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestChainableObject2 );


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

class TestChainableObject : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestChainableObject );
	CPPUNIT_TEST( testShouldFailIfInvokedTimesIsMoreThanExpectedTimes );
	CPPUNIT_TEST( testShouldFailIfReturnedTypeDoesNotMatchRequiredType );
	CPPUNIT_TEST( testShouldFailIfReturnedTypeDoesNotMatchRequiredType2 );
	CPPUNIT_TEST( testShouldFailIfInvocationOutOfOrder );
	CPPUNIT_TEST( testShouldFailIfInvocationOutOfOrder2 );
	CPPUNIT_TEST( testShouldSupportOrderingExpectationByBefore );
	CPPUNIT_TEST( testShouldSupportOrderingExpectationByAfter );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////
	void testShouldSupportOrderingExpectationByAfter()
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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(j, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(j, 2));
      foo.verify();
   }

	void testShouldFailIfInvocationOutOfOrder()
   {
      Foo foo;

      foo.method("foo")
         .expects(once())
         .with(eq(1), eq((unsigned long)2))
         .will(returnValue(10));

      foo.method("foo")
         .expects(once())
         .before("1")
         .with(eq(2), eq((unsigned long)2))
         .will(returnValue(10));

      int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      foo.verify();
   }

   void testShouldFailIfInvocationOutOfOrder2()
   {
      Foo foo;

      foo.method("foo")
         .expects(once())
         .with(eq(1), eq((unsigned long)2))
         .will(returnValue(10));

      foo.method("foo")
         .expects(once())
         .with(eq(2), eq((unsigned long)2))
			.after("1")
         .will(returnValue(10));

      int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
      foo.verify();
   }

	void testShouldFailIfReturnedTypeDoesNotMatchRequiredType2()
   {
		Foo foo;

		foo.method("foo")
			.defaults()
			.will(returnValue((long)10));

		foo.method("foo")
         .expects(once())
         .with(eq(1), eq((unsigned long)2))
	      .will(returnValue((long)10));

		int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
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
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }

	void testShouldFailIfInvokedTimesIsMoreThanExpectedTimes()
   {
		Foo foo;

		foo.method("foo")
         .expects(exactly(2))
         .with(eq(1), eq((unsigned long)4))
	      .will(returnValue(3));

		foo.method("foo")
         .expects(never())
         .with(eq(2), eq((unsigned long)2))
	      .will(returnValue(10));

		int i = 2;
      CPPUNIT_ASSERT_EQUAL(10, foo.foo(i, 2));
		foo.verify();
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestChainableObject );

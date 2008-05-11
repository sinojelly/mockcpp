
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

class TestReturnObjectList : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestReturnObjectList );
	CPPUNIT_TEST( testShouldSupportReturnObjectList );
	CPPUNIT_TEST( testShouldFailIfTheTypeOfAReturnObjectMismatch );
	CPPUNIT_TEST( testShouldFailIfThereIsNoAvailableObjectsToReturn );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////
	void testShouldSupportReturnObjectList()
   {
		Foo foo;

		foo.method("foo")
         .expects(exactly(3))
         .with(eq(1), eq((unsigned long)4))
	      .will(returnObjectList(3, 4, 5));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(3, foo.foo(i, 4));
      CPPUNIT_ASSERT_EQUAL(4, foo.foo(i, 4));
      CPPUNIT_ASSERT_EQUAL(5, foo.foo(i, 4));
		foo.verify();
   }

   void testShouldFailIfTheTypeOfAReturnObjectMismatch()
   {
		Foo foo;

		foo.method("foo")
         .expects(exactly(3))
         .with(eq(1), eq((unsigned long)4))
	      .will(returnObjectList(3, (long)4, 5));

		int i = 1;
      CPPUNIT_ASSERT_EQUAL(3, foo.foo(i, 4));
      CPPUNIT_ASSERT_EQUAL(4, foo.foo(i, 4));
      CPPUNIT_ASSERT_EQUAL(5, foo.foo(i, 4));
		foo.verify();
   }

   void testShouldFailIfThereIsNoAvailableObjectsToReturn()
   {
      Foo foo;

      foo.method("foo")
         .stubs()
         .with(eq(1), eq((unsigned long)4))
         .will(returnObjectList(3, 4, 5));

      int i = 1;
      CPPUNIT_ASSERT_EQUAL(3, foo.foo(i, 4));
      CPPUNIT_ASSERT_EQUAL(4, foo.foo(i, 4));
      CPPUNIT_ASSERT_EQUAL(5, foo.foo(i, 4));
      foo.foo(i,4);
      foo.verify();
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestReturnObjectList );


#include <cxxtest/TestSuite.h>
#include <Any.h>
#include <ChainableMockObject.h>
#include <InvocationMockBuilder.h>
#include <ChainingMockHelper.h>

using namespace mockcpp;

class Foo : public ChainableMockObject
{
public:
	Foo()
		: ChainableMockObject("Foo")
	{}

	int foo(int& i, unsigned long j)
	{
		return invoke<int>("foo")("foo",i, j);
	}
};

class TestReturnObjectList : public CxxTest::TestSuite
{
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

		TS_ASSERT_EQUALS(3, foo.foo(i, 4));
		TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo.foo(i, 4));

		foo.verify();
	}

	void testShouldThrowExceptionIfTheTypeOfAReturnObjectMismatch()
	{
		Foo foo;

		foo.method("foo")
		   .expects(exactly(3))
		   .with(eq(1), eq((unsigned long)4))
		   .will(returnObjectList(3, (long)4, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo.foo(i, 4));
		TS_ASSERT_THROWS(foo.foo(i,4), mockcpp::Exception);
		//TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo.foo(i, 4));

		foo.verify();
	}

	void testShouldThrowExceptionIfThereIsNoAvailableObjectsToReturn()
	{
		Foo foo;

		foo.method("foo")
		   .stubs()
		   .with(eq(1), eq((unsigned long)4))
		   .will(returnObjectList(3, 4, 5));

		int i = 1;

		TS_ASSERT_EQUALS(3, foo.foo(i, 4));
		TS_ASSERT_EQUALS(4, foo.foo(i, 4));
		TS_ASSERT_EQUALS(5, foo.foo(i, 4));

		TS_ASSERT_THROWS(foo.foo(i,4), mockcpp::Exception);

		foo.verify();
	}

};


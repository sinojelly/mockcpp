
#include <cppunit/extensions/HelperMacros.h>
#include <Any.h>
#include <RefAny.h>
#include <IsRef.h>

using namespace mockcpp;

class TestAny : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestAny );
	CPPUNIT_TEST( testShouldBeEmptyIfANewInstanceIsNotInitialized );
	CPPUNIT_TEST( testShouldNotBeEmptyIfAInstanceIsInitialized );
	CPPUNIT_TEST( testShouldBeCastableForSameType );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
	}

	void tearDown()
	{
	}

	/////////////////////////////////////////////////////////

	void testShouldBeEmptyIfANewInstanceIsNotInitialized()
	{
		Any i;

		CPPUNIT_ASSERT(i.empty());
	}

	void testShouldNotBeEmptyIfAInstanceIsInitialized()
	{
		Any i(0);

		CPPUNIT_ASSERT(!i.empty());
	}

	void testShouldBeCastableForSameType()
   {
		RefAny ref(10);

		CPPUNIT_ASSERT(any_castable<int>(ref));
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestAny );

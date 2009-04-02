
#include <cxxtest/TestSuite.h>
#include <Any.h>
#include <RefAny.h>
#include <IsRef.h>

using namespace mockcpp;
          
class TestAny: public CxxTest::TestSuite 
{
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

		TS_ASSERT(i.empty());
	}

	void testShouldNotBeEmptyIfAInstanceIsInitialized()
	{
		Any i(0);

		TS_ASSERT(!i.empty());
	}

	void testShouldBeCastableForSameType()
	{
		RefAny ref(10);

		TS_ASSERT(any_castable<int>(ref));
	}

};


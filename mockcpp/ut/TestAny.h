
#include <cxxtest/TestSuite.h>
#include <Any.h>
#include <RefAny.h>
#include <IsRef.h>

USING_MOCKCPP_NS
          
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

   void testShouldBeAbleStorePChar()
   {
		RefAny ref((char*)"abcd");

		TS_ASSERT(any_castable<char*>(ref));
   }
   
   void testShouldBeAbleStoreNullPchar()
   {
		RefAny ref((char*)0);

		TS_ASSERT(any_castable<char*>(ref));
   }
};


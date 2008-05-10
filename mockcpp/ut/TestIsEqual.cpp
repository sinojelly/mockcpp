
#include <cppunit/extensions/HelperMacros.h>
#include <Any.h>
#include <IsEqual.h>

using namespace mockcpp;

class TestIsEqual : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestIsEqual );
	CPPUNIT_TEST( testShouldMatchEqualValue );
	CPPUNIT_TEST( testShouldNotMatchInequalValue );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	void testShouldMatchEqualValue()
	{
      IsEqual<int> isEqual(10);

      CPPUNIT_ASSERT(isEqual.eval(10));
	}

   void testShouldNotMatchInequalValue()
   {
      IsEqual<int> isEqual(10);

      CPPUNIT_ASSERT(!isEqual.eval(11));
   }

};

CPPUNIT_TEST_SUITE_REGISTRATION( TestIsEqual );

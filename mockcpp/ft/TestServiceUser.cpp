
#include <cppunit/extensions/HelperMacros.h>

#include <ChainingMockHelper.h>
#include <MockService.h>

#include <ServiceUser.c>

using namespace mockcpp;

class TestService : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestService );
	CPPUNIT_TEST( test_func1_will_invoke_service_printf );
	CPPUNIT_TEST( test_func2_will_invoke_service_f1 );
	CPPUNIT_TEST( test_func2_will_invoke_service_f5 );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
      MOCKER(service_f5)
        .defaults()
        .will(returnValue((long)0));
	}

	void tearDown()
	{
      globalMockContextVerifyAndReset();
	}

	/////////////////////////////////////////////////////////

	void test_func1_will_invoke_service_printf()
   {
      MOCKER(service_printf)
        .expects(once())
        .with(eq(10), eq(20), eq(2.0))
        .will(returnValue(0));

      func1(); 
   }

   void test_func2_will_invoke_service_f1()
   {
      int i = 20;

      MOCKER(service_f1)
        .expects(once())
        .with(eq(10), eq<const int*>(&i));

      func2(&i);
   }

   void test_func2_will_invoke_service_f5()
   {
      int i = 10;

      MOCKER(service_f1)
        .expects(once());
     
      MOCKER(service_f5)
        .expects(once())
        .with(eq((const int&)i))
        .will(returnValue((long)2));

      CPPUNIT_ASSERT_EQUAL((long)2, func2(&i));
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestService );

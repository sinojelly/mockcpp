
#include <cppunit/extensions/HelperMacros.h>

#include <ChainingMockHelper.h>
#include <MockInterface.h>
#include <MockMethod.h>
#include <InterfaceUser.h>

using namespace mockcpp;

class TestInterfaceUser: public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestInterfaceUser );
	CPPUNIT_TEST( testShouldReturn_ERR_MOCKCPP_FAILED_IfOpenFileFailed );
	CPPUNIT_TEST( testShouldReturn_ERR_MOCKCPP_OPEN_IfFileIsNotOpenedSuccessfully );
	CPPUNIT_TEST( testShouldReturn_ERR_MOCKCPP_READ_IfReadFails );
	CPPUNIT_TEST( testShouldReturn_ERR_MOCKCPP_SUCCESS_AndPutContentIntoPassedInObjectIfEverythingGoesWell );
	CPPUNIT_TEST( testShouldReturnTheCalculatedValue );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp()
	{
	}

	void tearDown()
	{
      MOCKCPP_NS_OBJ_VERIFY_AND_RESET(Global);
	}

   void testShouldReturnTheCalculatedValue()
   {
      Object obj;

      obj.a = 10;
      obj.b = 1.2;

      MOCKER(doCalc)
        .expects(once())
        .with(eq(obj.a), eq((float)1.2))
        .will(returnValue((float)11.2));

      MockInterface* iface = new MockInterface;

      InterfaceUser user(iface);

      CPPUNIT_ASSERT_EQUAL((float)11.2, user.calc(obj));

      delete iface;
   }

	void testShouldReturn_ERR_MOCKCPP_FAILED_IfOpenFileFailed()
   {
      MockInterface* iface = new MockInterface;

      iface->method("open")
         .expects(once())
         .with(eq(std::string("file01")))
         .will(returnValue((Handle*)0));

      InterfaceUser user(iface);

      Object obj;
      CPPUNIT_ASSERT_EQUAL((error_t)ERR_MOCKCPP_FAILED, user.readObject("file01", obj));

      delete iface;
   }

   
	void testShouldReturn_ERR_MOCKCPP_OPEN_IfFileIsNotOpenedSuccessfully()
   {
      MockInterface* iface = new MockInterface;

      Handle* handle = new Handle;

      iface->method("open")
         .expects(once())
         .with(eq(std::string("file01")))
         .will(returnValue(handle))
         .id("open");

      iface->method("isOpen")
         .expects(once())
         .after("open")
         .will(returnValue(false));

      InterfaceUser user(iface);

      Object obj;

      CPPUNIT_ASSERT_EQUAL((error_t)ERR_MOCKCPP_OPEN, user.readObject("file01", obj));

      delete handle;
      delete iface;
   }

	void testShouldReturn_ERR_MOCKCPP_READ_IfReadFails()
   {
      MockInterface* iface = new MockInterface;

      Handle* handle = new Handle;
      Object obj;

      iface->method("open")
         .expects(once())
         .with(eq(std::string("file01")))
         .will(returnValue(handle))
         .id("open");

      iface->method("isOpen")
         .expects(once())
         .after("open")
         .will(returnValue(true))
         .id("isOpen");

      iface->method("read")
         .expects(once())
         .with(eq(handle), eq(&obj))
         .after("isOpen")
         .will(returnValue(-1));

      InterfaceUser user(iface);

      CPPUNIT_ASSERT_EQUAL((error_t)ERR_MOCKCPP_READ
                          , user.readObject("file01", obj));

      delete handle;
      delete iface;
   }

	void testShouldReturn_ERR_MOCKCPP_SUCCESS_AndPutContentIntoPassedInObjectIfEverythingGoesWell()
   {
      MockInterface* iface = new MockInterface;

      Handle* handle = new Handle;
      Object obj;

      iface->method("open")
         .expects(once())
         .with(eq(std::string("file01")))
         .will(returnValue(handle))
         .id("open");

      iface->method("isOpen")
         .expects(once())
         .after("open")
         .will(returnValue(true))
         .id("isOpen");

      Object obj1;
      obj1.a = 10;
      obj1.b = 1.2;

      iface->method("read")
         .expects(once())
         .with(eq(handle), outBoundP(&obj1))
         .after("isOpen")
         .will(returnValue(0));

      InterfaceUser user(iface);

      CPPUNIT_ASSERT_EQUAL((error_t)ERR_MOCKCPP_SUCCESS
                          , user.readObject("file01", obj));

      CPPUNIT_ASSERT_EQUAL(obj.a, obj1.a);
      CPPUNIT_ASSERT_EQUAL(obj.b, obj1.b);

      delete handle;
      delete iface;
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestInterfaceUser);

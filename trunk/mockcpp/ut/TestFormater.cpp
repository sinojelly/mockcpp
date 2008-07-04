
#include <cppunit/extensions/HelperMacros.h>
#include <Formatter.h>

using namespace mockcpp;

class TestFormatter : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestFormatter );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeObject );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeConstObject );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeReference );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeConstReference );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeObjectAddr );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNullObjectAddr );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeConstObjectAddr );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeString );
	CPPUNIT_TEST( testShouldBeAbleToStringnizePChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeConstPChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNullPChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNullConstPChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeDouble );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeDouble);
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeDouble);
	CPPUNIT_TEST( testShouldBeAbleToStringnizeZeroDotDouble);
	CPPUNIT_TEST( testShouldBeAbleToStringnizeDotDouble);
	CPPUNIT_TEST( testShouldBeAbleToStringnizeVerySmallDouble);
	CPPUNIT_TEST( testShouldBeAbleToStringnizeFloat );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeConstFloat );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeFloat );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeZeroDotFloat );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeDotFloat );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeVerySmallFloat );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeConstChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeUnsignedChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeChar );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeShort );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeUnsignedShort );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeShort );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeInt );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeUnsignedInt );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeInt );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeLong );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeUnsignedLong );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeLong );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeLongLong );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeUnsignedLongLong );
	CPPUNIT_TEST( testShouldBeAbleToStringnizeNegativeLongLong );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp()
	{
	}

	void tearDown()
	{
	}

	/////////////////////////////////////////////////////////

	class A { };

	void testShouldBeAbleToStringnizeConstReference()
	{
		A a;	
		const A& ref = a;

		std::string expected = std::string("([") + typeid(a).name() + "])unknown";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(ref));
	}

	void testShouldBeAbleToStringnizeReference()
	{
		A a;	
		A& ref = a;

		std::string expected = std::string("([") + typeid(a).name() + "])unknown";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(ref));
	}

	void testShouldBeAbleToStringnizeConstObject()
	{
		const A p = A();	

		std::string expected = std::string("([") + typeid(p).name() + "])unknown";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeObject()
	{
		A p;	

		std::string expected = std::string("([") + typeid(p).name() + "])unknown";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeNullObjectAddr()
	{
		A* p = 0;	

		std::string expected = std::string("([") + typeid(A).name() + "]*)NULL";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeObjectAddr()
	{
		A* p = (A*)0x12ab;	

		std::string expected = std::string("([") + typeid(A).name() + "]*)0x000012ab";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeConstObjectAddr()
	{
		const A* p = (const A*)0x12ab;	

		std::string expected = std::string("(const [") + typeid(A).name() + "]*)0x000012ab";
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeString()
	{
		std::string str("abc");
		std::string expected("(std::string)\"abc\"");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(str));
	}

	void testShouldBeAbleToStringnizePChar()
	{
		char* s = (char*)"abc";
        oss_t oss;
        oss << "(char*)" << (void*)s ;
      CPPUNIT_ASSERT_EQUAL(oss.str(), toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeConstPChar()
	{
		const char* s = "abc";
        oss_t oss;
        oss << "(const char*)" << (void*)s ;
      CPPUNIT_ASSERT_EQUAL(oss.str(), toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeNullPChar()
	{
		char* s = 0;
		std::string expected("(char*)NULL");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeNullConstPChar()
	{
		const char* s = 0;
		std::string expected("(const char*)NULL");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeDouble()
	{
		double d = 123.45;
		std::string expected("(double)123.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(d));
	}

	void testShouldBeAbleToStringnizeNegativeDouble()
   {
      double d = -123.45;
      std::string expected("(double)-123.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeZeroDotDouble()
   {
      double d = 0.45;
      std::string expected("(double)0.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeDotDouble()
   {
      double d = .45;
      std::string expected("(double)0.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(d));
   }

   void testShouldBeAbleToStringnizeVerySmallDouble()
   {
      double d = .0000000000000000000001;
      std::string expected("(double)1e-22");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(d));
   }


	void testShouldBeAbleToStringnizeFloat()
	{
		float f = 123.45;
		std::string expected("(float)123.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeConstFloat()
	{
		const float f = 123.45;
		std::string expected("(float)123.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeNegativeFloat()
	{
		float f = -123.45;
		std::string expected("(float)-123.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeZeroDotFloat()
	{
		float f = 0.45;
		std::string expected("(float)0.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeDotFloat()
	{
		float f = .45;
		std::string expected("(float)0.45");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeVerySmallFloat()
	{
		float f = .0000000000000000000001;
		std::string expected("(float)1e-22");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeChar()
	{
		char c = 0x12;
		std::string expected("(char)0x12/18");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeConstChar()
	{
		const char c = 0x12;
		std::string expected("(char)0x12/18");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeUnsignedChar()
	{
		unsigned char c = 0xa;
		std::string expected("(uchar)0xa/10");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeNegativeChar()
	{
		char c = -1;
		std::string expected("(char)0xff/-1");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeShort()
	{
		short s = 0x12;
		std::string expected("(short)0x12/18");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeUnsignedShort()
	{
		unsigned short s = 0x12;
		std::string expected("(ushort)0x12/18");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeNegativeShort()
	{
		short s = -1;
		std::string expected("(short)0xffff/-1");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeInt()
	{
		std::string expected("(int)0x4d2/1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(1234));
	}

	void testShouldBeAbleToStringnizeUnsignedInt()
	{
		unsigned int i = 1234;
		std::string expected("(uint)0x4d2/1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(i));
	}

   void testShouldBeAbleToStringnizeNegativeInt()
   {
		std::string expected("(int)0xfffffb2e/-1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(-1234));
   }
   
   void testShouldBeAbleToStringnizeLong()
   {
		long l = 1234;
		std::string expected("(long)0x4d2/1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(l));
   }

   void testShouldBeAbleToStringnizeUnsignedLong()
   {
		unsigned long l = 1234;
		std::string expected("(ulong)0x4d2/1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(l));
   }

   void testShouldBeAbleToStringnizeNegativeLong()
   {
		long l = -1234;
		std::string expected("(long)0xfffffb2e/-1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(l));
   }

	void testShouldBeAbleToStringnizeLongLong()
   {
      long long ll = 1234;
		std::string expected("(int64)0x4d2/1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(ll));
   }

	void testShouldBeAbleToStringnizeUnsignedLongLong()
   {
      unsigned long long ll = 1234;
		std::string expected("(uint64)0x4d2/1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(ll));
   }

	void testShouldBeAbleToStringnizeNegativeLongLong()
   {
      long long ll = -1234;
		std::string expected("(int64)0xfffffffffffffb2e/-1234");
      CPPUNIT_ASSERT_EQUAL(expected, toTypeAndValueString(ll));
   }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestFormatter );

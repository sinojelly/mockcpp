
#include <cxxtest/TestSuite.h>
#include <mockcpp/Formatter.h>
#include <stdio.h>

USING_MOCKCPP_NS

class TestFormatter : public CxxTest::TestSuite
{
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

	class A { };

	void testShouldBeAbleToStringnizeConstReference()
	{
		A a;	
		const A& ref = a;

		std::string expected = std::string("(") + getDemangledName(typeid(a)) + ")unknown";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(ref));
	}

	void testShouldBeAbleToStringnizeReference()
	{
		A a;	
		A& ref = a;

		std::string expected = std::string("(") + getDemangledName(typeid(a)) + ")unknown";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(ref));
	}

	void testShouldBeAbleToStringnizeConstObject()
	{
		const A p = A();	

		std::string expected = std::string("(") + getDemangledName(typeid(p)) + ")unknown";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeObject()
	{
		A p;	

		std::string expected = std::string("(") + getDemangledName(typeid(p)) + ")unknown";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeNullObjectAddr()
	{
		A* p = 0;	

		std::string expected = std::string("(") + getDemangledName(typeid(A)) + "*)NULL";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeObjectAddr()
	{
		A* p = (A*)0x12ab;	

		std::string expected = std::string("(") + getDemangledName(typeid(A)) + "*)0x000012ab";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeConstObjectAddr()
	{
		const A* p = (const A*)0x12ab;	

		std::string expected = std::string("(") + getDemangledName(typeid(A)) + " const*)0x000012ab";
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(p));
	}

	void testShouldBeAbleToStringnizeString()
	{
		std::string str("abc");
		std::string expected("(std::string)\"abc\"");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(str));
	}

	void testShouldBeAbleToStringnizePChar()
	{
		char* s = (char*)"abc";
		oss_t oss;
		oss << "(char*)" << (void*)s ;
		TS_ASSERT_EQUALS(oss.str(), toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeConstPChar()
	{
		const char* s = "abc";
		oss_t oss;
		oss << "(char const*)" << (void*)s ;
		TS_ASSERT_EQUALS(oss.str(), toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeNullPChar()
	{
		char* s = 0;
		std::string expected("(char*)NULL");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeNullConstPChar()
	{
		const char* s = 0;
		std::string expected("(char const*)NULL");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeDouble()
	{
		double d = 123.45;
		std::string expected("(double)123.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
	}

	void testShouldBeAbleToStringnizeNegativeDouble()
	{
		double d = -123.45;
		std::string expected("(double)-123.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
	}

	void testShouldBeAbleToStringnizeZeroDotDouble()
	{
		double d = 0.45;
		std::string expected("(double)0.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
	}

	void testShouldBeAbleToStringnizeDotDouble()
	{
		double d = .45;
		std::string expected("(double)0.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
	}

	void testShouldBeAbleToStringnizeVerySmallDouble()
	{
		double d = .0000000000000000000001;
		std::string expected("(double)1e-22");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(d));
	}


	void testShouldBeAbleToStringnizeFloat()
	{
		float f = 123.45;
		std::string expected("(float)123.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeConstFloat()
	{
		const float f = 123.45;
		std::string expected("(float)123.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeNegativeFloat()
	{
		float f = -123.45;
		std::string expected("(float)-123.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeZeroDotFloat()
	{
		float f = 0.45;
		std::string expected("(float)0.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeDotFloat()
	{
		float f = .45;
		std::string expected("(float)0.45");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeVerySmallFloat()
	{
		float f = .0000000000000000000001;
		std::string expected("(float)1e-22");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(f));
	}

	void testShouldBeAbleToStringnizeChar()
	{
		char c = 0x12;
		std::string expected("(char)0x12/18");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeConstChar()
	{
		const char c = 0x12;
		std::string expected("(char)0x12/18");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeUnsignedChar()
	{
		unsigned char c = 0xa;
		std::string expected("(unsigned char)0xa/10");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeNegativeChar()
	{
		char c = -1;
		std::string expected("(char)0xff/-1");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(c));
	}

	void testShouldBeAbleToStringnizeShort()
	{
		short s = 0x12;
		std::string expected("(short)0x12/18");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeUnsignedShort()
	{
		unsigned short s = 0x12;
		std::string expected("(unsigned short)0x12/18");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeNegativeShort()
	{
		short s = -1;
		std::string expected("(short)0xffff/-1");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(s));
	}

	void testShouldBeAbleToStringnizeInt()
	{
		std::string expected("(int)0x4d2/1234");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(1234));
	}

	void testShouldBeAbleToStringnizeUnsignedInt()
	{
		unsigned int i = 1234;
		std::string expected("(unsigned int)0x4d2/1234");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(i));
	}

	void testShouldBeAbleToStringnizeNegativeInt()
	{
		int i = -1234;

      char buf[50];
      ::sprintf(buf, "(int)0x%x/%d", i, i);

		std::string expected(buf);

		TS_ASSERT_EQUALS(expected, toTypeAndValueString(i));
	}
   
	void testShouldBeAbleToStringnizeLong()
	{
		long l = 1234;

      char buf[50];
      ::sprintf(buf, "(long)0x%lx/%ld", l, l);
		std::string expected(buf);

		TS_ASSERT_EQUALS(expected, toTypeAndValueString(l));
	}

	void testShouldBeAbleToStringnizeUnsignedLong()
	{
		unsigned long l = 1234;

      char buf[50];
      ::sprintf(buf, "(unsigned long)0x%lx/%ld", l, l);
		std::string expected(buf);
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(l));
	}

	void testShouldBeAbleToStringnizeNegativeLong()
	{
		long l = -1234;

      char buf[50];
      ::sprintf(buf, "(long)0x%lx/%ld", l, l);
		std::string expected(buf);

		TS_ASSERT_EQUALS(expected, toTypeAndValueString(l));
	}

	void testShouldBeAbleToStringnizeLongLong()
	{
#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
		long long ll = 1234;
		std::string expected("(long long)0x4d2/1234");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(ll));
#endif
	}

	void testShouldBeAbleToStringnizeUnsignedLongLong()
	{
#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
		unsigned long long ll = 1234;
		std::string expected("(unsigned long long)0x4d2/1234");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(ll));
#endif
	}

	void testShouldBeAbleToStringnizeNegativeLongLong()
	{
#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
		long long ll = -1234;
		std::string expected("(long long)0xfffffffffffffb2e/-1234");
		TS_ASSERT_EQUALS(expected, toTypeAndValueString(ll));
#endif
	}
};


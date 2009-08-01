
#include <cxxtest/TestSuite.h>

#include <MethodInfoReader.h>

class TestMethodInfoReader : public CxxTest::TestSuite
{
	struct Base0
   {
      virtual int  base00() = 0;
      virtual bool base01(int) const = 0;
      virtual ~Base0() {}
   };

   struct Base1
   {
      virtual void base10() = 0;
      virtual long base11(bool) const = 0;

      virtual ~Base1() {}
   };

   struct Interface: public Base0, public Base1
   {
      virtual void a() {}
      virtual void b(bool) {}
      void c() {}
   };
public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

   template <typename Method>
   int getIndexOfMethod(Method m)
   {
		return MOCKCPP_NS::getIndexOfMethod<Interface, Method>(m);
   }

	void testShouldBeAbleToCalcVptrIndex()
	{
      TS_ASSERT(getIndexOfMethod(&Interface::base00) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::base01) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::base10) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::base11) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::a) >= 0);
      TS_ASSERT(getIndexOfMethod(&Interface::b) >= 0);

      TS_ASSERT(getIndexOfMethod(&Interface::base00) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::base01) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::base10) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::base11) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::a) < 10);
      TS_ASSERT(getIndexOfMethod(&Interface::b) < 10);

      TS_ASSERT(getIndexOfMethod(&Interface::base00) != getIndexOfMethod(&Interface::base01));
      TS_ASSERT(getIndexOfMethod(&Interface::base10) != getIndexOfMethod(&Interface::base11));

      TS_ASSERT((getIndexOfMethod(&Interface::base00) != getIndexOfMethod(&Interface::a)) ||
                (getIndexOfMethod(&Interface::base10) != getIndexOfMethod(&Interface::a)));

      TS_ASSERT((getIndexOfMethod(&Interface::base01) != getIndexOfMethod(&Interface::a)) ||
                (getIndexOfMethod(&Interface::base11) != getIndexOfMethod(&Interface::a)));
	}

   void testShouldBeAbleToCalcVptrByBaseClass()
   {
      TS_ASSERT(getIndexOfMethod(&Base0::base00) >= 0);
      TS_ASSERT(getIndexOfMethod(&Base0::base01) >= 0);

      TS_ASSERT(getIndexOfMethod(&Base0::base00) < 10);
      TS_ASSERT(getIndexOfMethod(&Base0::base01) < 10);

      TS_ASSERT(getIndexOfMethod(&Base1::base10) >= 0);
      TS_ASSERT(getIndexOfMethod(&Base1::base11) >= 0);

      TS_ASSERT(getIndexOfMethod(&Base1::base10) < 10);
      TS_ASSERT(getIndexOfMethod(&Base1::base11) < 10);
   }

   template <typename Method>
   int getDeltaOfMethod(Method m)
   {
		return MOCKCPP_NS::getDeltaOfMethod<Interface, Method>(m);
   }

	void testShouldBeAbleToGetVtblIndex()
   {
      TS_ASSERT(getDeltaOfMethod(&Interface::base00) == 0 || \
                getDeltaOfMethod(&Interface::base00) == 1);

      TS_ASSERT(getDeltaOfMethod(&Interface::base10) == 0 || \
                getDeltaOfMethod(&Interface::base10) == 1);

      TS_ASSERT(getDeltaOfMethod(&Interface::a) == 0 || \
                getDeltaOfMethod(&Interface::a) == 1);
   }

	void testShouldBeEqualIf2MethodsDefinedInOneInterface()
   {
      TS_ASSERT(getDeltaOfMethod(&Interface::base00) == getDeltaOfMethod(&Interface::base01));
      TS_ASSERT(getDeltaOfMethod(&Interface::base10) == getDeltaOfMethod(&Interface::base11));
   }

	void testShouldNotBeEqualIf2MethodsDefinedInDifferentBaseInterface()
   {
      TS_ASSERT(getDeltaOfMethod(&Interface::base00) != getDeltaOfMethod(&Interface::base10));
   }

   void testShouldThrowAnExceptionIfTryToGetVtblIndexOfANonVirtualMethod()
   {
      TS_ASSERT_THROWS(getIndexOfMethod(&Interface::c), MOCKCPP_NS::Exception);
   }

   void testShouldThrowAnExceptionIfTryToGetVptrIndexOfANonVirtualMethod()
   {
      TS_ASSERT_THROWS(getDeltaOfMethod(&Interface::c), MOCKCPP_NS::Exception);
   }

   void testShouldThrowAnExceptionIfTryToGetAddressOfAVirtualMethod()
   {
      TS_ASSERT_THROWS(MOCKCPP_NS::getAddrOfMethod(&Interface::base00), MOCKCPP_NS::Exception);
   }
};


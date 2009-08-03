
#include <cxxtest/TestSuite.h>
#include <MemoryCheckPoint.h>
#include <DelegatedMethod.h>

class TestDelegatedMethod: public CxxTest::TestSuite
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

private:

   MemoryCheckPoint checkpoint;

public:

   void setUp()
   {
      checkpoint = mockcppSetCheckPoint();

   }
   void tearDown()
   {
      MOCKCPP_CHECK_POINT_VERIFY(checkpoint);
   }


	/////////////////////////////////////////////////////////

	void testShouldBeAbleToChooseCorrectDelegatedMethod()
	{
      bool isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int> >::IsConst;
      TS_ASSERT(!isConst);
      unsigned int numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int> >::NumberOfParameters;
      TS_ASSERT_EQUALS(0, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int> >::IsConst;
      TS_ASSERT(isConst);
      numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int> >::NumberOfParameters;
      TS_ASSERT_EQUALS(0, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int, float> >::IsConst;
      TS_ASSERT(!isConst);
      numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsList<int, float> >::NumberOfParameters;
      TS_ASSERT_EQUALS(1, numberOfParameters);

      /////////////////////////////////////////////////////////////////////////////////////////
      isConst = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int, float> >::IsConst;
      TS_ASSERT(isConst);
      numberOfParameters = MOCKCPP_NS::DelegatedMethod<0,0, MOCKCPP_NS::ArgumentsListConst<int, float> >::NumberOfParameters;
      TS_ASSERT_EQUALS(1, numberOfParameters);
	}

};



#include <cxxtest/TestSuite.h>

#include <MemoryCheckPoint.h>
#include <VirtualTable.h>
#include <IndexInvokableGetter.h>
#include <Invokable.h>

struct IndexInvokableGetterStub : public IndexInvokableGetter
{
	Invokable* getInvokable(unsigned int indexOfVtbl, unsigned int indexOfVptr = 0) const
   {
		return 0;
   }
};

struct TestMethodHolder
{
   long base11(bool p) const
   {
       return p?100:-100;
   }
};

class TestVirtualTable: public CxxTest::TestSuite
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

   void testShouldBeAbleToConvertToPointerToInterfaceType()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      VirtualTable vtbl(&indexInvokableGetter, sizeof(Interface)/sizeof(void*));

      Interface* pInterface = (Interface*) vtbl.toPointerToInterface();

      TS_ASSERT_THROWS(pInterface->a(), MOCKCPP_NS::Exception);
   }

   void testShouldThrowExceptionIfTheNumberOfVptrExceedsTheMaxSettingOfConfiguration()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      try {
         VirtualTable vtbl(&indexInvokableGetter, 8);
         TS_FAIL("Should throw an exception!");
      }
      catch(MOCKCPP_NS::Exception& e)
      {
      }
   }

   template <typename Method>
   int getIndexOfMethod(Method m)
   {
      return MOCKCPP_NS::getIndexOfMethod<Interface, Method>(m);
   }

   template <typename Method>
   int getDeltaOfMethod(Method m)
   {
      return MOCKCPP_NS::getDeltaOfMethod<Interface, Method>(m);
   }

   void testShouldBeAbleToSetMethod()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      VirtualTable vtbl(&indexInvokableGetter, sizeof(Interface)/sizeof(void*));

      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      vtbl.addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      Interface* pInterface = (Interface*) vtbl.toPointerToInterface();

      TestMethodHolder holder;

      TS_ASSERT_EQUALS(pInterface->base11(true), holder.base11(true));
      TS_ASSERT_EQUALS(pInterface->base11(false), holder.base11(false));
      TS_ASSERT(pInterface->base11(true) != pInterface->base11(false));
   }

   void testShouldThrowExceptionIfAMethodIsNotSet()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      VirtualTable vtbl(&indexInvokableGetter, sizeof(Interface)/sizeof(void*));

      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      vtbl.addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      Interface* pInterface = (Interface*) vtbl.toPointerToInterface();

      pInterface->base11(true);

      TS_ASSERT_THROWS(pInterface->base00(), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(pInterface->base01(0), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(pInterface->base10(), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(pInterface->a(), MOCKCPP_NS::Exception);
      TS_ASSERT_THROWS(pInterface->b(true), MOCKCPP_NS::Exception);
   }

   void testShouldThrowExceptionIfIndexOfVtblExceedsTheLimitationOfConfiguration()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      VirtualTable vtbl(&indexInvokableGetter, sizeof(Interface)/sizeof(void*));

      unsigned int indexOfVtbl = MOCKCPP_MAX_VTBL_SIZE;
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      TS_ASSERT_THROWS(vtbl.addMethod(methodAddr, indexOfVtbl, indexOfVptr), MOCKCPP_NS::Exception);
   }

   void testShouldThrowExceptionIfIndexOfVtblExceedsTheNumberOfVptr()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      unsigned int numberOfVptr = sizeof(Interface)/sizeof(void*);
      VirtualTable vtbl(&indexInvokableGetter, numberOfVptr);

      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = numberOfVptr;
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      TS_ASSERT_THROWS(vtbl.addMethod(methodAddr, indexOfVtbl, indexOfVptr), MOCKCPP_NS::Exception);
   }

   void testShouldBeAbleToGetPreviouslySetIndexInvokableGetterByReturnedPointerToInterface()
   {
      IndexInvokableGetterStub indexInvokableGetter;
      VirtualTable vtbl(&indexInvokableGetter, sizeof(Interface)/sizeof(void*));

      unsigned int indexOfVtbl = getIndexOfMethod(&Interface::base11);
      unsigned int indexOfVptr = getDeltaOfMethod(&Interface::base11);
      void* methodAddr = MOCKCPP_NS::getAddrOfMethod(&TestMethodHolder::base11);
 
      vtbl.addMethod(methodAddr, indexOfVtbl, indexOfVptr);

      Interface* pInterface = (Interface*) vtbl.toPointerToInterface();

      IndexInvokableGetter* getter = VirtualTable::getInvokableGetter(vtbl.toPointerToInterface(), 0);

      TS_ASSERT_EQUALS(getter, &indexInvokableGetter);
   }
};


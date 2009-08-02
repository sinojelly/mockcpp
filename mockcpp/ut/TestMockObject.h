
#include <cxxtest/TestSuite.h>

#include <MockObject.h>

using namespace mockcpp;

class TestMockObject : public CxxTest::TestSuite
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

public:
	void setUp() { }
	void tearDown() { }

	/////////////////////////////////////////////////////////

   // returnValue()
   void testShouldBeAbleReturnTheExpectedValue()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // once()
   void testShouldBeAbleSpecifyInvokeOnce()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(once()).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // once()
   void testShouldBeThrowExceptionIfInvokedTimesExceedsOnceButTheSpecifiedTimesIsOnce()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(once()).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());

       TS_ASSERT_THROWS(((Interface*)mock)->base00(), Exception);
   }

   // once()
   void testShouldBeThrowExceptionIfYouSpecifiedInvokingOnceButYouAcutallyDidNot()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(once()).will(returnValue(20));

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // exactly()
   void testShouldBeAbleSpecifieExactInvokingTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(exactly(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // exactly()
   void testShouldBeThrowExceptionIfInvokedTimesExceedsSpecifiedTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(exactly(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // exactly()
   void testShouldBeThrowExceptionIfInvokedTimesLessThanSpecifiedTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(exactly(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // atLeast()
   void testShouldSupportSpecifyingAtLeastTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atLeast(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // atLeast()
   void testShouldBeThrowExceptionIfInvokedTimesLessThanSpecifiedAtLeastTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atLeast(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());

       TS_ASSERT_THROWS(mock.verify(), Exception);
   }

   // atMost()
   void testShouldSupportSpecifyingAtMostTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atMost(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // atMost()
   void testShouldSupportSpecifyingAtMostTimes1()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atMost(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // atMost()
   void testShouldThrowExceptionIfInvokedTimesMoreThanSpecifiedAtLeastTimes()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(atMost(2)).will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_THROWS(((Interface*)mock)->base00(), Exception);
   }

   // never()
   void testShouldBeAbleToSpecifyNeverInvokeAnInvocation()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(never());
   }

   // never()
   void testShouldThrowAnExceptionIfYouAreTryingToInvokeAnInvocationWhichWasSpecifedNeverInvoked()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).expects(never()).will(returnValue(20));

       TS_ASSERT_THROWS(((Interface*)mock)->base00(), Exception);
   }

   // with()
   void testShouldBeAbleToSelectAppropriateInvocationToInvoke()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false));

       TS_ASSERT(((Interface*)mock)->base01(12));
       TS_ASSERT(((Interface*)mock)->base01(12));

       TS_ASSERT(!((Interface*)mock)->base01(21));
       TS_ASSERT(!((Interface*)mock)->base01(21));
   }

   // with()
   void testShouldThrowExceptionIfAnAppropriateInvocationWasNotSpecified()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false));

       TS_ASSERT_THROWS(((Interface*)mock)->base01(16), Exception);
   }

   // before()
   void testShouldSupportBeforeOnOneObject()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .before("1")
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(((Interface*)mock)->base01(12));
       TS_ASSERT(((Interface*)mock)->base01(12));

       TS_ASSERT(!((Interface*)mock)->base01(21));
       TS_ASSERT(!((Interface*)mock)->base01(21));
   }

   // before()
   void testShouldThrowAnExceptionIfYouDidNotInvokeTheOneFirstlyWhichYouSaidItShouldBeInvokedBeforeAnother()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .before("1")
           .with(eq(12))
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock)->base01(21));

       TS_ASSERT_THROWS(((Interface*)mock)->base01(12), Exception);
   }

   // before()
   void testShouldSupportBeforeOnDifferentObject()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .stubs()
           .before(mock1, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(((Interface*)mock0)->base01(12));
       TS_ASSERT(!((Interface*)mock1)->base01(12));
   }

   // before()
   void testShouldThrowAnExceptionIfYouDidNotInvokeTheOneFirstlyWhichYouSaidItShouldBeInvokedBeforeAnother1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .stubs()
           .before(mock1, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock1)->base01(12));
       TS_ASSERT_THROWS(((Interface*)mock0)->base01(12), Exception);
   }

   // after()
   void testShouldSupportAfterOnOneObject()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after("1")
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock)->base01(21));
       TS_ASSERT(!((Interface*)mock)->base01(21));

       TS_ASSERT(((Interface*)mock)->base01(12));
       TS_ASSERT(((Interface*)mock)->base01(12));
   }

   // after()
   void testShouldThrowAnExceptionIfYouHaveInvokedTheOneWhichYouSaidItShouldBeInvokedAfterAnother()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after("1")
           .will(returnValue(true));

       mock.method(&Interface::base01)
           .stubs()
           .with(eq(21))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT_THROWS(((Interface*)mock)->base01(12), Exception);
   }

   // after()
   void testShouldSupportAfterOnDifferentObject()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after(mock1, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock1)->base01(12));
       TS_ASSERT(((Interface*)mock0)->base01(12));
   }

   // after()
   void testShouldThrowAnExceptionIfYouHaveInvokedTheOneWhichYouSaidItShouldBeInvokedAfterAnother1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;

       mock0.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after(mock1, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT_THROWS(((Interface*)mock0)->base01(12), Exception);
   }
};


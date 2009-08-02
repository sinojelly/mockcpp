
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
      virtual long base11(const std::string&) const = 0;

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

   // will()
   void testShouldBeAbleReturnTheExpectedValue()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(returnValue(20));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
   }

   // then()
   void testShouldBeAbleToReturnTheExpectedValueAccordingToTheSequenceOfStubs()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(returnValue(20)).then(returnValue(10));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(10, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(10, ((Interface*)mock)->base00());
   }

   // then()
   void testShouldBeAbleToSupportMultipleThenSpecification()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00)
           .stubs()
           .will(returnValue(20))
           .then(returnValue(10))
           .then(returnValue(1))
           .then(returnValue(5));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(10, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(1, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(5, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(5, ((Interface*)mock)->base00());
   }

   // repeat()
   void testShouldBeAbleReturnValueRepeatedly()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(repeat(20, 2)).then(returnValue(10));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(10, ((Interface*)mock)->base00());
   }

   // repeat()
   void testShouldThrowExceptionAfterRepeatingSpecifiedTimesAndNoSubsequentStubSpecified()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(repeat(20, 2));

       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(20, ((Interface*)mock)->base00());
       
       TS_ASSERT_THROWS(((Interface*)mock)->base00(), Exception);
   }

   // increase()
   void testShouldBeAbleReturnValueIncrementallyWithinAScope()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(increase(1, 3)).then(returnValue(10));

       TS_ASSERT_EQUALS(1, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(2, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(3, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(10, ((Interface*)mock)->base00());
   }

   // increase()
   void testShouldBeAbleReturnValueIncrementallyWithoutEnding()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(increase(1)).then(returnValue(10));

       TS_ASSERT_EQUALS(1, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(2, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(3, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(4, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(5, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(6, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(7, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(8, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(9, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(10, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(11, ((Interface*)mock)->base00());
   }

   // throws()
   void testShouldBeAbleThrowAnException()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base00).stubs().will(increase(1, 3)).then(throws(10));

       TS_ASSERT_EQUALS(1, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(2, ((Interface*)mock)->base00());
       TS_ASSERT_EQUALS(3, ((Interface*)mock)->base00());
       TS_ASSERT_THROWS_EQUALS(((Interface*)mock)->base00(), int& e, e, 10);
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

   // startWith()
   void testShouldBeAbleToSelectAppropriateInvocationToInvokeByStartWith()
   {
       MockObject<Interface> mock;

       mock.method(&Interface::base11)
           .stubs()
           .with(startWith("abcd"))
           .will(returnValue((long)1));

       mock.method(&Interface::base11)
           .stubs()
           .with(startWith("1234"))
           .will(returnValue((long)2));

       TS_ASSERT_EQUALS(1, ((Interface*)mock)->base11("abcdefg"));
       TS_ASSERT_EQUALS(2, ((Interface*)mock)->base11("1234567"));
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

   // before()
   void testShouldSupportMultipleBeforeSpecification()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .stubs()
           .before(mock1, "1")
           .before(mock2, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(((Interface*)mock0)->base01(12));
       TS_ASSERT(!((Interface*)mock1)->base01(12));
       TS_ASSERT(!((Interface*)mock2)->base01(12));
   }

   // before()
   void testShouldThrowExceptionIfAnyOfOrderDefinedInBeforeSpecifactionIsBroken()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .stubs()
           .before(mock1, "1")
           .before(mock2, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock1)->base01(12));
       TS_ASSERT_THROWS(((Interface*)mock0)->base01(12), Exception);
   }

   // before()
   void testShouldThrowExceptionIfAnyOfOrderDefinedInBeforeSpecifactionIsBroken1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .stubs()
           .before(mock1, "1")
           .before(mock2, "1")
           .with(eq(12))
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock2)->base01(12));
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

   // after()
   void testShouldSupportSpecifyMultipleAfterConstraits()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after(mock1, "1")
           .after(mock2, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock1)->base01(12));
       TS_ASSERT(!((Interface*)mock2)->base01(12));
       TS_ASSERT(((Interface*)mock0)->base01(12));
   }

   // after()
   void testShouldThrowExceptionIfInvocationOrderIsNotAsAfterSpecification()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after(mock1, "1")
           .after(mock2, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock1)->base01(12));
       TS_ASSERT_THROWS(((Interface*)mock0)->base01(12), Exception);
   }

   // after()
   void testShouldThrowExceptionIfInvocationOrderIsNotAsAfterSpecification1()
   {
       MockObject<Interface> mock0;
       MockObject<Interface> mock1;
       MockObject<Interface> mock2;

       mock0.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .after(mock1, "1")
           .after(mock2, "1")
           .will(returnValue(true));

       mock1.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       mock2.method(&Interface::base01)
           .stubs()
           .with(eq(12))
           .will(returnValue(false))
           .id("1");

       TS_ASSERT(!((Interface*)mock2)->base01(12));
       TS_ASSERT_THROWS(((Interface*)mock0)->base01(12), Exception);
   }
};


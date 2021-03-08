
#include <cxxtest/TestSuite.h> 
#include <testngppst/runner/ResourceCheckPoint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>
#include <errno.h>

#include <mockcpp/mockcpp.hpp>

#include <testngpp/runner/TestCaseSandboxResultReporter.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>
#include <testngpp/internal/TestCaseInfoReader.h>

#include <testngpp/comm/PipeReadableChannel.h>
#include <testngpp/comm/PipeWrittableChannel.h>

//FIXME: avoid linux load error, undefined symbol: _ZN8testngpp11StupidTimer4stopEv
#include "../../src/utils/StupidTimer.cpp"

USING_MOCKCPP_NS
USING_TESTNGPP_NS

class TestTestCaseSandboxResultReporter: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   int sockets[2];

   ReadableChannel* rChannel;
   WrittableChannel* wChannel;

   MockObject<TestCaseInfoReader> testcase;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      int result = ::socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
      TS_ASSERT(result == 0);

      rChannel = new PipeReadableChannel(sockets[0]);
      wChannel = new PipeWrittableChannel(sockets[1]);
   }

   void tearDown()
   {
      delete rChannel;
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleReportStartEvent()
   {
      TestCaseSandboxResultReporter reporter(wChannel);

   	reporter.startTestCase(testcase);

      TS_ASSERT(rChannel->readByte() == 1);
   }

   void testShouldBeAbleReportEndEvent()
   {
      TestCaseSandboxResultReporter reporter(wChannel);

   	reporter.endTestCase(testcase,0,0);

      TS_ASSERT(rChannel->readByte() == 2);
   }

   void testShouldBeAbleReportErrorEvent()
   {
      TestCaseSandboxResultReporter reporter(wChannel);
      std::string msg("test case error");

   	reporter.addCaseError(testcase, msg);

      TS_ASSERT(rChannel->readByte() == 3);
      TS_ASSERT(rChannel->readString() == msg);
   }

   void testShouldBeAbleReportFailureEvent()
   {
      TestCaseSandboxResultReporter reporter(wChannel);
      AssertionFailure failure("TestNothing.h", 11, "test case error");

   	reporter.addCaseFailure(testcase, failure);

      TS_ASSERT(rChannel->readByte() == 4);
      TS_ASSERT(rChannel->readString() == failure.getFileName());
      TS_ASSERT(rChannel->readInt() == failure.getLineOfFile());
   }

};


class TestTestCaseSandboxResultDecoder: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   int sockets[2];

   ReadableChannel* rChannel;
   WrittableChannel* wChannel;

   MockObject<TestCaseInfoReader> testcase;

   MockObject<TestCaseResultCollector> collector;

   TestCaseSandboxResultReporter *reporter;

   TestCaseSandboxResultDecoder *decoder;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      int result = ::socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
      TS_ASSERT(result == 0);

      rChannel = new PipeReadableChannel(sockets[0]);
      wChannel = new PipeWrittableChannel(sockets[1]);

      reporter = new TestCaseSandboxResultReporter(wChannel);
     
      decoder = new TestCaseSandboxResultDecoder(rChannel, testcase, collector, true);

      collector.METHOD(TestCaseResultCollector::startTestCase).defaults();
      collector.METHOD(TestCaseResultCollector::endTestCase).defaults();

   }

   void tearDown()
   {
      collector.reset();

      delete reporter;
      delete decoder;

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToDecodeStartEvent()
   {
      reporter->startTestCase(testcase);

      //////////////////////////////////////////////
      collector.METHOD(TestCaseResultCollector::startTestCase)
               .expects(once());

      TS_ASSERT(!decoder->decode());

      decoder->flush(false);

      collector.verify();
   }

   void testShouldBeAbleToDecodeEndEventAndReturnTrueToRepresentTheCaseHasFinished()
   {
      reporter->startTestCase(testcase);
      reporter->endTestCase(testcase,0,0);

      //////////////////////////////////////////////
      collector.METHOD(TestCaseResultCollector::endTestCase)
               .expects(once());

      TS_ASSERT(!decoder->decode());
      TS_ASSERT(decoder->decode());

      decoder->flush(false);

      collector.verify();
   }

   void testShouldBeAbleToDecodeErrorEvent()
   {
      std::string msg("test case error");

      reporter->startTestCase(testcase);
      reporter->addCaseError(testcase, msg);

      //////////////////////////////////////////////
      collector.METHOD(TestCaseResultCollector::addCaseError)
               .expects(once())
               .with(any(), eq(msg));

      TS_ASSERT(!decoder->decode());
      TS_ASSERT(!decoder->decode());

      decoder->flush(false);

      collector.verify();
   }

   void testShouldBeAbleToDecodeFailureEvent()
   {
      AssertionFailure failure("TestNothing.h", 11, "test case error");

      reporter->startTestCase(testcase);
      reporter->addCaseFailure(testcase, failure);

      //////////////////////////////////////////////
      collector.METHOD(TestCaseResultCollector::addCaseFailure)
               .expects(once())
               .with(any(), eq(failure));

      TS_ASSERT(!decoder->decode());
      TS_ASSERT(!decoder->decode());

      decoder->flush(false);

      collector.verify();
   }

   void testShouldBeAbleToDecodeFailureEventEvenIfTheSocketWasClosedByPeer()
   {
      AssertionFailure failure("TestNothing.h", 11, "test case error");

      reporter->startTestCase(testcase);
      reporter->addCaseFailure(testcase, failure);

      //////////////////////////////////////////////
      wChannel->close();

      collector.METHOD(TestCaseResultCollector::addCaseFailure)
               .expects(exactly(1))
               .with(any(), eq(failure));

      TS_ASSERT(!decoder->decode());
      TS_ASSERT(!decoder->decode());

      decoder->flush(false);

      collector.verify();
   }

   void testShouldThrowInternalErrorIfReceivedEndEventBeforeStartTestCase()
   {
      reporter->endTestCase(testcase, 0, 0);
      TS_ASSERT_THROWS(decoder->decode(), Error);
   }

   void testShouldThrowInternalErrorIfReceivedErrorEventBeforeStartTestCase()
   {
      std::string msg("test case error");
      reporter->addCaseError(testcase, msg);

      TS_ASSERT_THROWS(decoder->decode(), Error);
   }

   void testShouldThrowInternalErrorIfReceivedFailureEventBeforeStartTestCase()
   {
      AssertionFailure failure("TestNothing.h", 11, "test case error");
      reporter->addCaseFailure(testcase, failure);

      TS_ASSERT_THROWS(decoder->decode(), Error);
   }

   void testShouldThrowInternalErrorIfReceivedAnotherStartEvent()
   {
      reporter->startTestCase(testcase);
      reporter->startTestCase(testcase);

      decoder->decode();

      TS_ASSERT_THROWS(decoder->decode(), Error);
   }

   void testShouldThrowInternalErrorIfReceivedAnotherEndEvent()
   {
      reporter->startTestCase(testcase);
      reporter->endTestCase(testcase,0,0);
      reporter->endTestCase(testcase,0,0);

      decoder->decode();
      decoder->decode();

      TS_ASSERT_THROWS(decoder->decode(), Error);
   }

   void testShouldThrowInternalErrorIfReceivedErrorEventAfterEndEvent()
   {
      reporter->startTestCase(testcase);
      reporter->endTestCase(testcase,0,0);

      std::string msg("test case error");
      reporter->addCaseError(testcase, msg);

      decoder->decode();
      decoder->decode();

      TS_ASSERT_THROWS(decoder->decode(), Error);
   }

	void testShouldThrowInternalErrorIfReceivedFailureEventAfterEndEvent()
	{
		reporter->startTestCase(testcase);
		reporter->endTestCase(testcase,0,0);

      AssertionFailure failure("TestNothing.h", 11, "test case error");
      reporter->addCaseFailure(testcase, failure);

		decoder->decode();
		decoder->decode();

		TS_ASSERT_THROWS(decoder->decode(), Error);
	}
   
   void testShouldReportToCollectorNothingBeforeStartEventReceived()
   {
      //////////////////////////////////////////////
      collector.METHOD(TestCaseResultCollector::startTestCase)
               .expects(never());

      decoder->flush(false);

      collector.verify();
   }

   void testShouldReportToCollectorCrashEventEvenStartEventWasNotReceived()
   {
      //////////////////////////////////////////////
      collector.METHOD(TestCaseResultCollector::startTestCase)
               .expects(once());

      collector.METHOD(TestCaseResultCollector::addCaseCrash)
               .expects(once());

      decoder->flush(true);

      collector.verify();
   }
   
   void testShouldNotReportCrashEventAfterEndEventReceived()
   {
      reporter->startTestCase(testcase);
      reporter->endTestCase(testcase,0,0);

      collector.METHOD(TestCaseResultCollector::addCaseCrash)
               .expects(never());

      decoder->decode();
      decoder->decode();

      decoder->flush(true);

      collector.verify();
   }
};

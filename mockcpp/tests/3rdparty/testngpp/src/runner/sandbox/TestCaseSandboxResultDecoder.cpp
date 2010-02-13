
#include <sstream>
#include <list>
#include <errno.h>

#include <testngpp/AssertionFailure.h>

#include <testngpp/runner/InternalError.h>
#include <testngpp/runner/TestCaseSandboxResultReporter.h>
#include <testngpp/runner/TestCaseSandboxResultDecoder.h>

#include <testngpp/comm/WrittableChannel.h>
#include <testngpp/comm/ReadableChannel.h>

TESTNGPP_NS_START

struct TestCaseSandboxResultDecoderImpl
{
	void addCaseError(const std::string& msg);
	void addCaseFailure(const AssertionFailure& failure);

   AssertionFailure readAssertionFailure();
   void handleAssertionFailure();
   void handleError();
   void handleInternalError();
   void handleStartCase();
   void handleEndCase();
   void flushRegularEvents();
   void flushErrorEvents();
   void flushFailureEvents();
   void flushEndEvent();

   bool decode();
   void flush(bool crashed);

   TestCaseSandboxResultDecoderImpl(ReadableChannel* ch
             , const TestCaseInfoReader* tc
             , TestCaseResultCollector* rc
             , bool report)
      : channel(ch), testcase(tc), collector(rc)
      , startReceived(false), endReceived(false)
      , errorReceived(false), failureReceived(false)
      , crashInformed(false), reportSuccess(report)
   {}

   ~TestCaseSandboxResultDecoderImpl()
   {
      if(channel != 0)
      { delete channel; }
   }

   bool hasError() const
   { return errorReceived || failureReceived || crashInformed; }

   ReadableChannel* channel; // Y

   const TestCaseInfoReader* testcase; // X
   TestCaseResultCollector* collector; // X

   typedef std::list<std::string> Errors;
   typedef std::list<AssertionFailure> Failures;
   
   Errors errors;
   Failures failures;
   bool startReceived;
   bool endReceived;
   bool errorReceived;
   bool failureReceived;
   bool crashInformed;
   bool reportSuccess;
};

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::addCaseError(const std::string& msg)
{
   if(!startReceived || endReceived || crashInformed)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1001));
   }

   errors.push_back(msg);

   errorReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::addCaseFailure(const AssertionFailure& failure)
{
   if(!startReceived || endReceived || crashInformed)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1002));
   }
   failures.push_back(failure);

   failureReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::flushErrorEvents()
{
   Errors::iterator error = errors.begin();
   for(; error != errors.end(); error++)
   {
      collector->addCaseError(testcase, (*error));
   }

   errors.clear();
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::flushFailureEvents()
{
   Failures::iterator failure = failures.begin();
   for(; failure != failures.end(); failure++)
   {
      collector->addCaseFailure(testcase, (*failure));
   }

   failures.clear();
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::flushEndEvent()
{
   if(endReceived)
   {
      collector->endTestCase(testcase);
   }
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::flushRegularEvents()
{
   if(!startReceived)
   {
      return;
   }

   bool shouldReport = reportSuccess;

   if( errorReceived || failureReceived || crashInformed)
   {
      shouldReport = true;
   }

   if(!shouldReport)
   { 
      return;
   }

   collector->startTestCase(testcase);

   flushErrorEvents();
   flushFailureEvents();

   flushEndEvent();
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::flush(bool crashed)
{
   if(crashInformed)
   {
      return;
   }

   flushRegularEvents();

   if(crashed && !endReceived)
   {
      collector->addCaseCrash(testcase);
      collector->endTestCase(testcase);
      crashInformed = true;
   }
}

/////////////////////////////////////////////////////////////////////////
namespace
{
   const unsigned char startCmd = 1;
   const unsigned char endCmd = 2;
   const unsigned char errorCmd = 3;
   const unsigned char failureCmd = 4;
}

/////////////////////////////////////////////////////////////
AssertionFailure
TestCaseSandboxResultDecoderImpl::readAssertionFailure()
{
   std::string file = channel->readString();
   int line = channel->readInt();
   std::string reason = channel->readString();
   return AssertionFailure(file, line, reason);
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::handleAssertionFailure()
{
   AssertionFailure failure = readAssertionFailure();
   addCaseFailure(failure);
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::handleError()
{
   std::string errMsg = channel->readString();
   addCaseError(errMsg);
}

/////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::handleInternalError()
{
   const char * err = TESTNGPP_INTERNAL_ERROR(1003);
   addCaseError(err);
   throw Error(err);
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::handleStartCase()
{
   if(startReceived || endReceived || errorReceived || failureReceived || crashInformed)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1004));
   }

   startReceived = true;
}

/////////////////////////////////////////////////////////////////////////
void
TestCaseSandboxResultDecoderImpl::handleEndCase()
{
   if(endReceived || !startReceived || crashInformed)
   {
      throw Error(TESTNGPP_INTERNAL_ERROR(1005));
   }
   endReceived = true;
}
/////////////////////////////////////////////////////////////////////////
bool TestCaseSandboxResultDecoderImpl::decode()
{
   switch(channel->readByte())
   {
   case startCmd:
      handleStartCase(); break;
   case endCmd:
      handleEndCase();
      return true;
   case errorCmd:
      handleError(); break;
   case failureCmd:
      handleAssertionFailure(); break;
   default:
      handleInternalError();
   }
   return false;
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultDecoder::
TestCaseSandboxResultDecoder
      ( ReadableChannel* channel
      , const TestCaseInfoReader* testcase
      , TestCaseResultCollector* collector
      , bool shouldReport)
      : This(new TestCaseSandboxResultDecoderImpl
          (channel, testcase, collector, shouldReport))
{
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultDecoder::~TestCaseSandboxResultDecoder()
{
   delete This;
}

/////////////////////////////////////////////////////////////////////////
bool TestCaseSandboxResultDecoder::decode()
{
   return This->decode();
}

/////////////////////////////////////////////////////////////////////////
bool TestCaseSandboxResultDecoder::hasError() const
{
   return This->hasError();
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultDecoder::flush(bool crashed)
{
   This->flush(crashed);
}

/////////////////////////////////////////////////////////////////////////

TESTNGPP_NS_END


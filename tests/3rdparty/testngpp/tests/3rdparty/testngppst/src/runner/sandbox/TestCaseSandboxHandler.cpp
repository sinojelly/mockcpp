
#include <testngppst/comm/ExceptionKeywords.h>

#include <testngppst/internal/TestCase.h>

#include <testngppst/comm/PipeWrittableChannel.h>
#include <testngppst/listener/TestCaseResultCollector.h>

#include <testngppst/runner/TestCaseSandboxHandler.h>
#include <testngppst/runner/TestCaseSandboxResultReporter.h>
#include <testngppst/runner/TestCaseRunner.h>


TESTNGPPST_NS_START

//////////////////////////////////////////////////////
struct TestCaseSandboxHandlerImpl
{
   TestCaseSandboxHandlerImpl(const TestCase* tc,
          TestCaseRunner* tcRunner)
      : testcase(tc), runner(tcRunner)
   {}

	void handle(ChannelId channelId);

   const TestCase* testcase;
   TestCaseRunner* runner;
};

//////////////////////////////////////////////////////
void
TestCaseSandboxHandlerImpl::
handle(ChannelId channelId)
{
   TestCaseResultCollector* reporter = \
         new TestCaseSandboxResultReporter( \
            new PipeWrittableChannel(channelId));
   
   __TESTNGPPST_DO
   {
      runner->run(const_cast<TestCase*>(testcase), reporter);
   }
   __TESTNGPPST_CLEANUP
   {
      delete reporter;
   }
   __TESTNGPPST_DONE
}

//////////////////////////////////////////////////////
TestCaseSandboxHandler::
TestCaseSandboxHandler
   ( const TestCase* testcase
   , TestCaseRunner* runner)
   : This(new TestCaseSandboxHandlerImpl(testcase, runner))
{
}

//////////////////////////////////////////////////////
TestCaseSandboxHandler::
~TestCaseSandboxHandler()
{
   delete This;
}

//////////////////////////////////////////////////////
void
TestCaseSandboxHandler::
handle(ChannelId channelId)
{
   This->handle(channelId);
}

//////////////////////////////////////////////////////

TESTNGPPST_NS_END



#include <testcpp/runner/TestCaseSandboxHandler.h>
#include <testcpp/runner/TestCaseResultCollector.h>
#include <testcpp/runner/TestCaseSandboxResultReporter.h>
#include <testcpp/runner/TestCaseRunner.h>
#include <testcpp/internal/TestCase.h>
#include <testcpp/comm/PipeWrittableChannel.h>

TESTCPP_NS_START

//////////////////////////////////////////////////////
struct TestCaseSandboxHandlerImpl
{
   TestCaseSandboxHandlerImpl(TestCase* tc,
          TestFixtureDesc* tfd,
          TestCaseRunner* tcRunner)
      : testcase(tc), fixture(tfd), runner(tcRunner)
   {}

	void handle(ChannelId channelId);

   TestCase* testcase;
   TestFixtureDesc* fixture;
   TestCaseRunner* runner;
};


//////////////////////////////////////////////////////
void
TestCaseSandboxHandlerImpl::handle(ChannelId channelId)
{
   TestCaseResultCollector* reporter = \
         new TestCaseSandboxResultReporter(new PipeWrittableChannel(channelId));
   
   try {
      runner->run(fixture, testcase, reporter);
   }
   catch(...)
   {
      delete reporter;
      throw;
   }

   delete reporter;
}

//////////////////////////////////////////////////////
TestCaseSandboxHandler::TestCaseSandboxHandler(TestCase* testcase,
          TestFixtureDesc* fixture,
          TestCaseRunner* runner)
   : This(new TestCaseSandboxHandlerImpl(testcase, fixture, runner))
{
}

//////////////////////////////////////////////////////
TestCaseSandboxHandler::~TestCaseSandboxHandler()
{
   delete This;
}

//////////////////////////////////////////////////////
void
TestCaseSandboxHandler::handle(ChannelId channelId)
{
   This->handle(channelId);
}

//////////////////////////////////////////////////////

TESTCPP_NS_END


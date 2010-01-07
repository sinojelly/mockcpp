
#include <sys/types.h>
#include <sys/socket.h>

#include <testcpp/Error.h>

#include <testcpp/comm/PipeReadableChannel.h>

#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestCase.h>

#include <testcpp/runner/EOFError.h>
#include <testcpp/runner/TestCaseRunner.h>
#include <testcpp/runner/Sandbox.h>
#include <testcpp/runner/EnvironmentCleaner.h>
#include <testcpp/runner/TestCaseSandboxHandler.h>
#include <testcpp/runner/TestCaseSandboxResultDecoder.h>
#include <testcpp/runner/TestCaseSandbox.h>
#include <testcpp/runner/TestCaseResultCollector.h>


TESTCPP_NS_START

////////////////////////////////////////////////////////
struct TestCaseSandboxImpl
{
   TestCaseSandboxImpl()
     : sandbox(0), decoder(0), finished(false)
   {}

   SandboxId getSandboxId() const
   { return sandbox->getSandboxId(); }
 
   ChannelId getChannelId() const
   {
     return sandbox->getChannelId();
   }

   void handle() throw (EOFError, Error);

   ~TestCaseSandboxImpl()
   {
      if(sandbox != 0)
         delete sandbox;

      if(decoder != 0)
         delete decoder;
   }

   Sandbox* sandbox;
   TestCaseSandboxResultDecoder* decoder;
   bool finished;
};

////////////////////////////////////////////////////////
void TestCaseSandboxImpl::handle() throw (EOFError, Error)
{
   if(sandbox->isDead())
   {
      return;
   }

   try
   {
	   bool result = decoder->decode();
      if(result && !finished)
      {
         finished = true;
         decoder->flush(false);
      }
   }
   catch(EOFError&)
   {
      if(!finished)
      {
         decoder->flush(true);
      }

      sandbox->die();

      finished = true;

      return;
   }
}

////////////////////////////////////////////////////////
TestCaseSandbox::TestCaseSandbox()
   : This(new TestCaseSandboxImpl())
{}

////////////////////////////////////////////////////////
TestCaseSandbox::~TestCaseSandbox()
{
	delete This;
}

////////////////////////////////////////////////////////
ChannelId TestCaseSandbox::getChannelId() const
{
   return This->getChannelId();
}

////////////////////////////////////////////////////////
void
TestCaseSandbox::handle() throw (EOFError, Error)
{
   This->handle();
}

////////////////////////////////////////////////////////
bool
TestCaseSandbox::isDead() const
{
   return This->sandbox->isDead();
}
////////////////////////////////////////////////////////
void
TestCaseSandbox::cleanup()
{
   This->sandbox->cleanup();
}
////////////////////////////////////////////////////////
TestCaseSandbox*
TestCaseSandbox::createInstance(EnvironmentCleaner* cleaner, \
          TestCase* testcase, \
          TestFixtureDesc* fixture, \
          TestCaseRunner* runner,
          TestCaseResultCollector* collector)
{
   TestCaseSandboxHandler handler(testcase, fixture, runner);
   Sandbox* sandbox = Sandbox::createInstance(cleaner, &handler);
   if(sandbox == 0)
   {
      throw Error("system error: cannot create object");
   }

   TestCaseSandbox* tcSandbox = new TestCaseSandbox();

   tcSandbox->This->decoder = \
         new TestCaseSandboxResultDecoder
            ( new PipeReadableChannel(sandbox->getChannelId())
            , testcase
            , collector);

   tcSandbox->This->sandbox = sandbox;

   return tcSandbox;
}

TESTCPP_NS_END


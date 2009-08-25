
// for select
#include <sys/select.h>
#include <errno.h>
#include <list>
#include <algorithm>
#include <string.h>

#include <testcpp/internal/TestFixtureDesc.h>
#include <testcpp/internal/TestCase.h>

#include <testcpp/runner/TestFixtureSandboxRunner.h>
#include <testcpp/runner/TestCaseRunner.h>
#include <testcpp/runner/TestCaseSandboxResultReporter.h>
#include <testcpp/runner/TestCaseSandboxResultDecoder.h>
#include <testcpp/runner/TestFixtureResultCollector.h>
#include <testcpp/runner/TestCaseSandbox.h>
#include <testcpp/runner/EnvironmentCleaner.h>
#include <testcpp/runner/TestCaseFilter.h>

TESTCPP_NS_START

///////////////////////////////////////////////////////
struct TestFixtureSandboxRunnerImpl : public EnvironmentCleaner
{
   typedef std::list<TestCaseSandbox*> List;

	TestFixtureSandboxRunnerImpl(unsigned int maxCurrentProcess, TestCaseRunner* runner)
      : maxProcess(maxCurrentProcess), caseRunner(runner), index(0)
   {}

	~TestFixtureSandboxRunnerImpl()
   {
      cleanUp();
   }

	void run(TestFixtureDesc* fixture
      , TestFixtureResultCollector* resultCollector
      , const TestCaseFilter* filter);

   void setupListeners();
   void createSandbox( TestFixtureDesc* fixture, unsigned int i
             , TestFixtureResultCollector* resultCollector);


   void createSandboxes(TestFixtureDesc* fixture
             , TestFixtureResultCollector* resultCollector
             , const TestCaseFilter* filter);

   void cleanUpDeadSandboxes();

   void process(TestFixtureDesc* fixture);
   void handleEvent(int nfds, TestFixtureDesc* fixture);

   void cleanUp();

   const unsigned int maxProcess;
   TestCaseRunner* caseRunner;
   unsigned int    index;
   fd_set          fds;
   int             maxfd;
   List sandboxes;
};

////////////////////////////////////////////////////
namespace 
{
   static void removeSandbox(TestCaseSandbox* sandbox)
   {
      delete sandbox;
   }
}

////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::cleanUp()
{
   std::for_each(sandboxes.begin(), sandboxes.end(), removeSandbox);
   sandboxes.clear();
}

////////////////////////////////////////////////////
namespace
{
    static bool isDead(TestCaseSandbox* sandbox)
    {
       return sandbox->isDead();  
    }
}

////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::cleanUpDeadSandboxes()
{
   while(1)
   {
      List::iterator i = std::find_if(sandboxes.begin(), sandboxes.end(), isDead);
      if(i == sandboxes.end())
      {
         break;
      }

      (*i)->cleanup();
      delete *i;
      sandboxes.erase(i);
   }
}

////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::
createSandbox( TestFixtureDesc* fixture, unsigned int i
             , TestFixtureResultCollector* resultCollector)
{
   TestCaseSandbox* sandbox = \
         TestCaseSandbox::createInstance( this, fixture->getTestCase(i)
                                        , fixture, caseRunner, resultCollector);
   sandboxes.push_back(sandbox);
}

////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::
createSandboxes( TestFixtureDesc* fixture
               , TestFixtureResultCollector* resultCollector
               , const TestCaseFilter* filter)
{
   unsigned int numberOfTestCases = fixture->getNumberOfTestCases();
   unsigned int i = index;
   for(; i < numberOfTestCases && sandboxes.size() < maxProcess; i++)
   {
      if(filter->isCaseMatch((const TestCaseInfoReader*)fixture->getTestCase(i)))
      {
         createSandbox(fixture, i, resultCollector);
      }
   }

   index = i;
}


/////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::setupListeners()
{
   FD_ZERO(&fds);
   maxfd = 0;

   List::iterator i = sandboxes.begin();
   for(; i != sandboxes.end(); i++)
   {
      FD_SET((*i)->getChannelId(), &fds);
      maxfd = maxfd < (*i)->getChannelId() ? (*i)->getChannelId() : maxfd;
   }
}

///////////////////////////////////////////////////////
namespace
{
   static void handleSandboxEvent(TestCaseSandbox* sandbox)
   {
      try{
         sandbox->handle();
      }
      catch(...)
      {
         throw;
      }
   }
}
///////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::handleEvent(int nfds, TestFixtureDesc* fixture)
{
   List::iterator i = sandboxes.begin();
   for(; i != sandboxes.end(); i++)
   {
      if(FD_ISSET((*i)->getChannelId(), &fds))
      {
         handleSandboxEvent(*i);
         if(--nfds <= 0)
         {
            break;
         }
      }
   }

   cleanUpDeadSandboxes();
}

///////////////////////////////////////////////////////
void TestFixtureSandboxRunnerImpl::process(TestFixtureDesc* fixture)
{
   setupListeners();

   int nfds = 0;
   do{
      nfds = ::select(maxfd + 1, &fds, 0, 0, 0);
   }while(nfds == 0 || (nfds < 0 && errno == EAGAIN));

   if(nfds < 0)
   {
      throw Error(strerror(errno));
   }

   handleEvent(nfds, fixture);
}

///////////////////////////////////////////////////////
void
TestFixtureSandboxRunnerImpl::run(TestFixtureDesc* fixture
        , TestFixtureResultCollector* resultCollector
        , const TestCaseFilter* filter)
{
   index = 0;

   while(1)
   {
      createSandboxes(fixture, resultCollector, filter);
      if(sandboxes.size() == 0)
      {
         break;
      }

      process(fixture);
   }
}

///////////////////////////////////////////////////////
TestFixtureSandboxRunner::TestFixtureSandboxRunner(
     unsigned int maxCurrentProcess
   , TestCaseRunner* caseRunner)
   : This(new TestFixtureSandboxRunnerImpl(maxCurrentProcess, caseRunner))
{
}

///////////////////////////////////////////////////////
TestFixtureSandboxRunner::~TestFixtureSandboxRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
void
TestFixtureSandboxRunner::run(TestFixtureDesc* fixture
      , TestFixtureResultCollector* resultCollector
      , const TestCaseFilter* filter)
{
   This->run(fixture, resultCollector, filter);
}

///////////////////////////////////////////////////////

TESTCPP_NS_END


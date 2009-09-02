
#include <iostream>

#include <testcpp/Error.h>

#include <testcpp/runner/TestSuiteRunner.h>
#include <testcpp/runner/LTTestSuiteLoader.h>
#include <testcpp/runner/LTTestListenerLoader.h>
#include <testcpp/runner/SimpleTestResultDispatcher.h>
#include <testcpp/runner/SimpleTestResultReporter.h>
#include <testcpp/runner/SimpleTestCaseResultReporter.h>
#include <testcpp/runner/SimpleTestSuiteResultReporter.h>
#include <testcpp/runner/TestFixtureRunnerFactory.h>
#include <testcpp/runner/InternalError.h>
#include <testcpp/runner/TestRunner.h>
#include <testcpp/runner/TestFilter.h>
#include <testcpp/runner/TestFilterFactory.h>

TESTCPP_NS_START

struct TestRunnerImpl
{
   typedef std::list<TestListenerLoader*> Listeners;

   Listeners listeners;

   SimpleTestResultReporter* reporter;
   SimpleTestSuiteResultReporter* suiteReporter;
   SimpleTestCaseResultReporter* caseReporter;
   SimpleTestResultDispatcher* dispatcher;
   TestSuiteLoader* loader;
   TestFixtureRunner * fixtureRunner;
   TestSuiteRunner * suiteRunner;
   bool hasFailures;

   TestRunnerImpl();
   ~TestRunnerImpl();

   
   void createSuiteRunner(bool useSandbox, unsigned int maxConcurrent);
   void runTestSuite( const std::string& suitePath
                    , const TestFilter* filter);
   void runTests( const TestRunner::StringList& suites,
                  const TestFilter* filter);

   void loadListener(TestRunnerContext* context, \
            const TestRunner::StringList& searchingPaths,
            const std::string& listenerName);

   void loadListeners(TestRunnerContext* context, \
            const TestRunner::StringList& searchingPaths,
            const TestRunner::StringList& listenerNames);

   void clearListeners();
};

///////////////////////////////////////////////////////
TestRunnerImpl::TestRunnerImpl()
   : caseReporter(new SimpleTestCaseResultReporter())
   , dispatcher(new SimpleTestResultDispatcher())
   , loader(new LTTestSuiteLoader())
   , fixtureRunner(0)
   , suiteRunner(0)
   , hasFailures(false)
{
   suiteReporter = new SimpleTestSuiteResultReporter(caseReporter);
   reporter = new SimpleTestResultReporter(suiteReporter);
   dispatcher->registerTestCaseListener(caseReporter);
   dispatcher->registerTestSuiteListener(suiteReporter);
   dispatcher->registerListener(reporter);
}

///////////////////////////////////////////////////////
void TestRunnerImpl::clearListeners()
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      delete (*i);
   }

   listeners.clear();
}

///////////////////////////////////////////////////////
TestRunnerImpl::~TestRunnerImpl()
{
   if(suiteRunner != 0)
   {
      delete suiteRunner;
   }

   if(fixtureRunner != 0)
   {
      TestFixtureRunnerFactory::
           destroyInstance(fixtureRunner);
   }

   delete loader;
   delete dispatcher;
   delete caseReporter;
   delete reporter;
   
   clearListeners();
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::
loadListener( TestRunnerContext* context
            , const TestRunner::StringList& searchingPaths
            , const std::string& listenerName)
{
   try
   {
      TestListenerLoader* loader = \
         new LTTestListenerLoader(listenerName);
      loader->load(context, searchingPaths);
      listeners.push_back(loader);
   }
   catch(Error& e)
   {
      std::cerr << "error occured while loading listener " 
                << listenerName 
                << " : " 
                << e.what() << std::endl;
   }
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::
loadListeners( TestRunnerContext* context \
             , const TestRunner::StringList& searchingPaths
             , const TestRunner::StringList& listenerNames)
{
   TestRunner::StringList::const_iterator i = listenerNames.begin();
   for(; i != listenerNames.end(); i++)
   {
      loadListener(context, searchingPaths, *i);
   }
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::createSuiteRunner(bool useSandbox, unsigned int maxConcurrent)
{
   fixtureRunner = \
      TestFixtureRunnerFactory:: \
         createInstance(useSandbox, maxConcurrent);

   suiteRunner = new TestSuiteRunner(loader, fixtureRunner);
}

///////////////////////////////////////////////////////
void TestRunnerImpl::runTestSuite
          ( const std::string& suitePath
          , const TestFilter* filter)
{
   try
   {
     suiteRunner->run(suitePath, dispatcher, filter);
   }
   catch(Error& e)
   {
      std::cerr << e.what() << std::endl;
      hasFailures = true;
   }
   catch(...)
   {
      std::cerr << TESTCPP_INTERNAL_ERROR(5001) << std::endl;
      hasFailures = true;
   }
}

///////////////////////////////////////////////////////
void
TestRunnerImpl::runTests(const TestRunner::StringList& suites,
                         const TestFilter* filter)
{
   dispatcher->startTest();

   TestRunner::StringList::const_iterator i = suites.begin();
   for(; i != suites.end(); i++)
   {
      runTestSuite(*i, filter);
   }

   dispatcher->endTest();

   if(reporter->getNumberOfUnsuccessfulTestCases() > 0 || 
      reporter->getNumberOfUnloadableSuites() > 0)
   {
      hasFailures = true;
   }
}

///////////////////////////////////////////////////////
TestRunner::TestRunner()
   : This(new TestRunnerImpl())
{
}

///////////////////////////////////////////////////////
TestRunner::~TestRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
TestResultReporter* 
TestRunner::getTestResultReporter() const
{
   return This->reporter;
}

///////////////////////////////////////////////////////
TestSuiteResultReporter* 
TestRunner::getTestSuiteResultReporter() const
{
   return This->suiteReporter;
}

///////////////////////////////////////////////////////
TestCaseResultReporter* 
TestRunner::getTestCaseResultReporter() const
{
   return This->caseReporter;
}

///////////////////////////////////////////////////////
void
TestRunner::registerTestListener(TestListener* listener)
{
   This->dispatcher->registerListener(listener);
}

///////////////////////////////////////////////////////
int
TestRunner::runTests( bool useSandbox
                    , unsigned int maxConcurrent
                    , const TestRunner::StringList& suitePaths
                    , const TestRunner::StringList& listenerNames
                    , const TestRunner::StringList& searchingPathsOfListeners
                    , const TestRunner::StringList& fixtures)
{
   This->createSuiteRunner(useSandbox, maxConcurrent);
   This->loadListeners(this, searchingPathsOfListeners, listenerNames);
   const TestFilter* filter = TestFilterFactory::getFilter(fixtures);

   This->runTests(suitePaths, filter);

   TestFilterFactory::returnFilter(filter);

   return This->hasFailures ? -2 : 0;
}

///////////////////////////////////////////////////////

TESTCPP_NS_END


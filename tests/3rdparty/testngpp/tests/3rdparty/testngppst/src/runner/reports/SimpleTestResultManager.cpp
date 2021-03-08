
#include <iostream>

#include <testngppst/comm/ExceptionKeywords.h>

#include <testngppst/utils/InternalError.h>

#include <testngppst/internal/Error.h>

#include <testngppst/runner/SimpleTestResultDispatcher.h>
#include <testngppst/runner/SimpleTestResultReporter.h>
#include <testngppst/runner/SimpleTestCaseResultReporter.h>
#include <testngppst/runner/SimpleTestSuiteResultReporter.h>

#include <testngppst/runner/loaders/TestListenerLoader.h>
#include <testngppst/runner/loaders/TestListenerLoaderFactory.h>
#include <testngppst/runner/SimpleTestResultManager.h>

TESTNGPPST_NS_START

struct SimpleTestResultManagerImpl
{
   typedef std::list<TestListenerLoader*> Loaders;

   Loaders loaders;

   TestListenerLoaderFactory* loaderFactory;

   SimpleTestResultReporter* reporter;
   SimpleTestSuiteResultReporter* suiteReporter;
   SimpleTestCaseResultReporter* caseReporter;

   SimpleTestResultDispatcher* dispatcher;

   SimpleTestResultManagerImpl(TestListenerLoaderFactory* factory);
   ~SimpleTestResultManagerImpl();

   void loadListener \
            ( const StringList& searchingPaths
            , const std::string& listenerName);

   void loadListeners \
            ( const StringList& searchingPaths \
            , const StringList& listenerNames);

   void clearListeners();
};

///////////////////////////////////////////////////////
SimpleTestResultManagerImpl::
SimpleTestResultManagerImpl(TestListenerLoaderFactory* factory)
   : loaderFactory(factory)
{
   dispatcher = new SimpleTestResultDispatcher();

   caseReporter = new SimpleTestCaseResultReporter();
   suiteReporter = new SimpleTestSuiteResultReporter(caseReporter);
   reporter = new SimpleTestResultReporter(suiteReporter);

   dispatcher->registerTestCaseListener(caseReporter);
   dispatcher->registerTestSuiteListener(suiteReporter);
   dispatcher->registerListener(reporter);
}

///////////////////////////////////////////////////////
void SimpleTestResultManagerImpl::clearListeners()
{
   Loaders::iterator i = loaders.begin();
   for(; i != loaders.end(); i++)
   {
      delete (*i);
   }

   loaders.clear();
}

///////////////////////////////////////////////////////
SimpleTestResultManagerImpl::
~SimpleTestResultManagerImpl()
{
   delete loaderFactory;
   delete suiteReporter;
   delete caseReporter;
   delete reporter;
   
   delete dispatcher;

   clearListeners();
}

///////////////////////////////////////////////////////
void
SimpleTestResultManagerImpl::
loadListener( const StringList& searchingPaths
            , const std::string& cl)
{
   __TESTNGPPST_TRY
   {
      TestListenerLoader* loader = loaderFactory->create();
      TestListener* listener = \
         loader->load( searchingPaths, cl \
                     , reporter \
                     , suiteReporter \
                     , caseReporter);
      dispatcher->registerListener(listener);
      loaders.push_back(loader);
   }
   __TESTNGPPST_CATCH(Error& e)
   {
      std::cerr << "error occured while loading listener " 
                << cl
                << " : " 
                << e.what() << std::endl;
   }
   __TESTNGPPST_END_TRY
}

///////////////////////////////////////////////////////
void
SimpleTestResultManager::
load( const StringList& searchingPaths
    , const StringList& listenerNames)
{
   StringList::Type::const_iterator i = listenerNames.get().begin();
   for(; i != listenerNames.get().end(); i++)
   {
      This->loadListener(searchingPaths, *i);
   }
}

///////////////////////////////////////////////////////
void
SimpleTestResultManager::startTest()
{
   This->dispatcher->startTest();
}

///////////////////////////////////////////////////////
void
SimpleTestResultManager::
endTest(unsigned int secs, unsigned int usecs)
{
   This->dispatcher->endTest(secs, usecs);
}

///////////////////////////////////////////////////////
bool
SimpleTestResultManager::hasFailure() const
{
   return This->reporter->getNumberOfUnsuccessfulTestCases() > 0
       || This->reporter->getNumberOfUnloadableSuites() > 0 
       || This->reporter->getNumberOfErrorFixtures() > 0 ;
}
///////////////////////////////////////////////////////
TestResultCollector*
SimpleTestResultManager::getResultCollector() const
{
   return This->dispatcher;
}

///////////////////////////////////////////////////////
SimpleTestResultManager::
SimpleTestResultManager(TestListenerLoaderFactory* loaderFactory)
   : This(new SimpleTestResultManagerImpl(loaderFactory))
{
}

///////////////////////////////////////////////////////
SimpleTestResultManager::
~SimpleTestResultManager()
{
   delete This;
}

///////////////////////////////////////////////////////

TESTNGPPST_NS_END


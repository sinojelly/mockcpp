
#include <list>
#include <iostream>

#include <testngpp/runner/SimpleTestResultDispatcher.h>
#include <testngpp/runner/TestCaseListener.h>
#include <testngpp/runner/TestSuiteListener.h>
#include <testngpp/runner/TestListener.h>
#include <testngpp/internal/TestCaseInfoReader.h>


TESTNGPP_NS_START

///////////////////////////////////////////////////////////
struct SimpleTestResultDispatcherImpl
{
   typedef std::list<TestListener*> Listeners;
   typedef std::list<TestCaseListener*> CaseListeners;
   typedef std::list<TestSuiteListener*> SuiteListeners;

   Listeners listeners;
   CaseListeners caseListeners;
   SuiteListeners suiteListeners;

   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseSkipped(const TestCaseInfoReader*);
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*);

   void startTestFixture(TestFixtureInfoReader*);
   void endTestFixture(TestFixtureInfoReader*);
   void addFixtureError(TestFixtureInfoReader*, const std::string&);
   void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&);

   void startTestSuite(TestSuiteInfoReader*);
   void endTestSuite(TestSuiteInfoReader*);
   void addSuiteError(TestSuiteInfoReader*, const std::string&);

   void startTagsFiltering(const TaggableObjFilter*);
   void endTagsFiltering(const TaggableObjFilter*);

   void startTest();
   void endTest();
   void addError(const std::string&);
   
};

///////////////////////////////////////////////////////////
SimpleTestResultDispatcher::SimpleTestResultDispatcher()
   : This(new SimpleTestResultDispatcherImpl)
{}

///////////////////////////////////////////////////////////
SimpleTestResultDispatcher::~SimpleTestResultDispatcher()
{
   delete This;
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
registerListener(TestListener* listener)
{
   if(listener == 0)
   {
      return;
   }

   This->listeners.push_back(listener);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
registerTestCaseListener(TestCaseListener* listener)
{
   if(listener == 0)
   {
      return;
   }

   This->caseListeners.push_back(listener);
}

///////////////////////////////////////////////////////////
TestCaseListener* SimpleTestResultDispatcher::
unregisterTestCaseListener(TestCaseListener* listener)
{
   This->caseListeners.remove(listener);
   return listener;
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
registerTestSuiteListener(TestSuiteListener* listener)
{
   if(listener == 0)
   {
      return;
   }

   This->suiteListeners.push_back(listener);
}

///////////////////////////////////////////////////////////
TestSuiteListener*
SimpleTestResultDispatcher::
unregisterTestSuiteListener(TestSuiteListener* listener)
{
   This->suiteListeners.remove(listener);
   return listener;
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseCrash(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseCrash(testcase);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   notifyAddCaseCrash(caseListeners, testcase);
   notifyAddCaseCrash(suiteListeners, testcase);
   notifyAddCaseCrash(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseCrash(const TestCaseInfoReader* testcase)
{
   This->addCaseCrash(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseSkipped(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseSkipped(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   notifyAddCaseSkipped(caseListeners, testcase);
   notifyAddCaseSkipped(suiteListeners, testcase);
   notifyAddCaseSkipped(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseSkipped(const TestCaseInfoReader* testcase)
{
   This->addCaseSkipped(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseError(T& listeners, 
   const TestCaseInfoReader* testcase, const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseError(testcase, msg);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
   notifyAddCaseError(caseListeners, testcase, msg);
   notifyAddCaseError(suiteListeners, testcase, msg);
   notifyAddCaseError(listeners, testcase, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
{
   This->addCaseError(testcase, msg);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseFailure(T& listeners, 
   const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseFailure(testcase, failure);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   notifyAddCaseFailure(caseListeners, testcase, failure);
   notifyAddCaseFailure(suiteListeners, testcase, failure);
   notifyAddCaseFailure(listeners, testcase, failure);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   This->addCaseFailure(testcase, failure);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartCase(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestCase(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestCase(const TestCaseInfoReader* testcase)
{
   notifyStartCase(caseListeners, testcase);
   notifyStartCase(suiteListeners, testcase);
   notifyStartCase(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestCase(const TestCaseInfoReader* testcase)
{
   This->startTestCase(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndCase(T& listeners, const TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestCase(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestCase(const TestCaseInfoReader* testcase)
{
   notifyEndCase(caseListeners, testcase);
   notifyEndCase(suiteListeners, testcase);
   notifyEndCase(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestCase(const TestCaseInfoReader* testcase)
{
   This->endTestCase(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartFixture(T& listeners, TestFixtureInfoReader* fixture)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestFixture(fixture);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestFixture(TestFixtureInfoReader* fixture)
{
   notifyStartFixture(suiteListeners, fixture);
   notifyStartFixture(listeners, fixture);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestFixture(TestFixtureInfoReader* fixture)
{
   This->startTestFixture(fixture);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndFixture(T& listeners, TestFixtureInfoReader* fixture)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestFixture(fixture);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestFixture(TestFixtureInfoReader* fixture)
{
   notifyEndFixture(suiteListeners, fixture);
   notifyEndFixture(listeners, fixture);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestFixture(TestFixtureInfoReader* fixture)
{
   This->endTestFixture(fixture);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddFixtureError(T& listeners
       , TestFixtureInfoReader* fixture
       , const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addFixtureError(fixture, msg);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addFixtureError( TestFixtureInfoReader* fixture
               , const std::string& msg)
{
   notifyAddFixtureError(suiteListeners, fixture, msg);
   notifyAddFixtureError(listeners, fixture, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addFixtureError(TestFixtureInfoReader* fixture, const std::string& msg)
{
   This->addFixtureError(fixture, msg);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddFixtureFailure(T& listeners
       , TestFixtureInfoReader* fixture
       , const AssertionFailure& failure)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addFixtureFailure(fixture, failure);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure)
{
   notifyAddFixtureFailure(suiteListeners, fixture, failure);
   notifyAddFixtureFailure(listeners, fixture, failure);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure)
{
   This->addFixtureFailure(fixture, failure);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartSuite(T& listeners
       , TestSuiteInfoReader* suite)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestSuite(suite);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestSuite(TestSuiteInfoReader* suite)
{
   notifyStartSuite(suiteListeners, suite);
   notifyStartSuite(listeners, suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestSuite(TestSuiteInfoReader* suite)
{
   This->startTestSuite(suite);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndSuite(T& listeners
       , TestSuiteInfoReader* suite)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestSuite(suite);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestSuite(TestSuiteInfoReader* suite)
{
   notifyEndSuite(suiteListeners, suite);
   notifyEndSuite(listeners, suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->endTestSuite(suite);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifySuiteError(T& listeners
       , TestSuiteInfoReader* suite
       , const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addSuiteError(suite, msg);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg )
{
   notifySuiteError(suiteListeners, suite, msg);
   notifySuiteError(listeners, suite, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg )
{
   This->addSuiteError(suite, msg);
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcherImpl::
startTagsFiltering(const TaggableObjFilter* filter)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTagsFiltering(filter);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
startTagsFiltering(const TaggableObjFilter* filter)
{
   This->startTagsFiltering(filter);
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcherImpl::
endTagsFiltering(const TaggableObjFilter* filter) 
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTagsFiltering(filter);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
endTagsFiltering(const TaggableObjFilter* filter) 
{
   This->endTagsFiltering(filter);
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcherImpl::
startTest()
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTest();
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::startTest()
{
   This->startTest();
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::endTest()
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTest();
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::endTest()
{
   This->endTest();
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addError(const std::string& msg)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addError(msg);
   }
}

///////////////////////////////////////////////////////////
void
SimpleTestResultDispatcher::
addError(const std::string& msg)
{
   This->addError(msg);
}

///////////////////////////////////////////////////////////

TESTNGPP_NS_END

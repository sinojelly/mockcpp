
#include <list>

#include <testcpp/runner/SimpleTestResultDispatcher.h>
#include <testcpp/runner/TestListener.h>
#include <testcpp/runner/TestCaseListener.h>
#include <testcpp/internal/TestCaseInfoReader.h>


TESTCPP_NS_START

///////////////////////////////////////////////////////////
struct SimpleTestResultDispatcherImpl
{
   typedef std::list<TestListener*> Listeners;
   typedef std::list<TestCaseListener*> CaseListeners;

   Listeners listeners;
   CaseListeners caseListeners;

   void addCaseCrash(TestCaseInfoReader*);
   void addCaseError(TestCaseInfoReader*, const std::string&);
   void addCaseFailure(TestCaseInfoReader*, const AssertionFailure&);
   void startTestCase(TestCaseInfoReader*);
   void endTestCase(TestCaseInfoReader*);

   void startTestFixture(TestFixtureInfoReader*);
   void endTestFixture(TestFixtureInfoReader*);
   void addFixtureError(TestFixtureInfoReader*, const std::string&);
   void addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure&);

   void startTestSuite(TestSuiteInfoReader*);
   void endTestSuite(TestSuiteInfoReader*);
   void addSuiteError(TestSuiteInfoReader*, const std::string&);
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
template <typename T>
void notifyAddCaseCrash(T& listeners, TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseCrash(testcase);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseCrash(TestCaseInfoReader* testcase)
{
   notifyAddCaseCrash(caseListeners, testcase);
   notifyAddCaseCrash(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseCrash(TestCaseInfoReader* testcase)
{
   This->addCaseCrash(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseError(T& listeners, 
   TestCaseInfoReader* testcase, const std::string& msg)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseError(testcase, msg);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
   notifyAddCaseError(caseListeners, testcase, msg);
   notifyAddCaseError(listeners, testcase, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
   This->addCaseError(testcase, msg);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyAddCaseFailure(T& listeners, 
   TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addCaseFailure(testcase, failure);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   notifyAddCaseFailure(caseListeners, testcase, failure);
   notifyAddCaseFailure(listeners, testcase, failure);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   This->addCaseFailure(testcase, failure);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyStartCase(T& listeners, TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestCase(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestCase(TestCaseInfoReader* testcase)
{
   notifyStartCase(caseListeners, testcase);
   notifyStartCase(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestCase(TestCaseInfoReader* testcase)
{
   This->startTestCase(testcase);
}

///////////////////////////////////////////////////////////
template <typename T>
void notifyEndCase(T& listeners, TestCaseInfoReader* testcase)
{
   typename T::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestCase(testcase);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestCase(TestCaseInfoReader* testcase)
{
   notifyEndCase(caseListeners, testcase);
   notifyEndCase(listeners, testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestCase(TestCaseInfoReader* testcase)
{
   This->endTestCase(testcase);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestFixture(TestFixtureInfoReader* fixture)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestFixture(fixture);
   }
}
///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestFixture(TestFixtureInfoReader* fixture)
{
   This->startTestFixture(fixture);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestFixture(TestFixtureInfoReader* fixture)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestFixture(fixture);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestFixture(TestFixtureInfoReader* fixture)
{
   This->endTestFixture(fixture);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addFixtureError(TestFixtureInfoReader* fixture, const std::string& msg)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addFixtureError(fixture, msg);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addFixtureError(TestFixtureInfoReader* fixture, const std::string& msg)
{
   This->addFixtureError(fixture, msg);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addFixtureFailure(fixture, failure);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure)
{
   This->addFixtureFailure(fixture, failure);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
startTestSuite(TestSuiteInfoReader* suite)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->startTestSuite(suite);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
startTestSuite(TestSuiteInfoReader* suite)
{
   This->startTestSuite(suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
endTestSuite(TestSuiteInfoReader* suite)
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->endTestSuite(suite);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
endTestSuite(TestSuiteInfoReader* suite)
{
   This->endTestSuite(suite);
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcherImpl::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg )
{
   Listeners::iterator i = listeners.begin();
   for(; i != listeners.end(); i++)
   {
      (*i)->addSuiteError(suite, msg);
   }
}

///////////////////////////////////////////////////////////
void SimpleTestResultDispatcher::
addSuiteError(TestSuiteInfoReader* suite, const std::string& msg )
{
   This->addSuiteError(suite, msg);
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

TESTCPP_NS_END


#include <iostream>

#include <testngppst/internal/TestCase.h>

#include <testngppst/listener/TestFixtureResultCollector.h>

#include <testngppst/runner/SimpleTestHierarchyRunner.h>
#include <testngppst/runner/TestHierarchyHandler.h>
#include <testngppst/runner/TestCaseRunner.h>
#include <testngppst/runner/TestCaseFilter.h>

TESTNGPPST_NS_START

///////////////////////////////////////////////////////
struct SimpleTestHierarchyRunnerImpl 
{
	SimpleTestHierarchyRunnerImpl(TestCaseRunner* runner)
      : caseRunner(runner)
   {}

	void run(TestHierarchyHandler* hierarchy
      , TestFixtureResultCollector* resultCollector);

   TestCaseRunner* caseRunner; // X
};

///////////////////////////////////////////////////////
void
SimpleTestHierarchyRunnerImpl::run(TestHierarchyHandler* hierarchy
        , TestFixtureResultCollector* resultCollector)
{
   for(unsigned int i = 0; i < hierarchy->numberOfTestCasesInSched(); i++)
   {
      TestHierarchyHandler::ValueType test = hierarchy->getTestCase(i);
      TestCase* testcase = const_cast<TestCase*>(test.first);
      bool result = caseRunner->run(testcase, resultCollector, test.second);
      hierarchy->testDone(testcase, result);
   }
}

///////////////////////////////////////////////////////
SimpleTestHierarchyRunner::
SimpleTestHierarchyRunner(TestCaseRunner* caseRunner)
   : This(new SimpleTestHierarchyRunnerImpl(caseRunner))
{
}

///////////////////////////////////////////////////////
SimpleTestHierarchyRunner::~SimpleTestHierarchyRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
void
SimpleTestHierarchyRunner::run(TestHierarchyHandler* hierarchy
      , TestFixtureResultCollector* resultCollector)
{
   This->run(hierarchy, resultCollector);
}

///////////////////////////////////////////////////////

TESTNGPPST_NS_END


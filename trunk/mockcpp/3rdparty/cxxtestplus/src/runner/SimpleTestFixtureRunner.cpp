
#include <testcpp/internal/TestFixtureDesc.h>
#include <testcpp/internal/TestCase.h>

#include <testcpp/runner/SimpleTestFixtureRunner.h>
#include <testcpp/runner/TestCaseRunner.h>
#include <testcpp/runner/TestFixtureResultCollector.h>
#include <testcpp/runner/TestCaseFilter.h>

TESTCPP_NS_START

///////////////////////////////////////////////////////
struct SimpleTestFixtureRunnerImpl 
{
	SimpleTestFixtureRunnerImpl(TestCaseRunner* runner)
      : caseRunner(runner)
   {}

	void run(TestFixtureDesc* fixture
      , TestFixtureResultCollector* resultCollector
      , const TestCaseFilter* filter);

   TestCaseRunner* caseRunner;
};

///////////////////////////////////////////////////////
void
SimpleTestFixtureRunnerImpl::run(TestFixtureDesc* fixture
        , TestFixtureResultCollector* resultCollector
        , const TestCaseFilter* filter)
{
   unsigned int numberOfTestCases = fixture->getNumberOfTestCases();
   for(unsigned int i=0; i<numberOfTestCases; i++)
   {
      TestCase* testcase = fixture->getTestCase(i);
      if(filter->isCaseMatch((const TestCaseInfoReader*)testcase))
      {
         caseRunner->run(fixture, testcase, resultCollector);
      }
   }
}

///////////////////////////////////////////////////////
SimpleTestFixtureRunner::SimpleTestFixtureRunner(TestCaseRunner* caseRunner)
   : This(new SimpleTestFixtureRunnerImpl(caseRunner))
{
}

///////////////////////////////////////////////////////
SimpleTestFixtureRunner::~SimpleTestFixtureRunner()
{
   delete This;
}

///////////////////////////////////////////////////////
void
SimpleTestFixtureRunner::run(TestFixtureDesc* fixture
      , TestFixtureResultCollector* resultCollector
      , const TestCaseFilter* filter)
{
   This->run(fixture, resultCollector, filter);
}

///////////////////////////////////////////////////////

TESTCPP_NS_END


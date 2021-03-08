
#include <iostream>

#include <testngppst/internal/TestSuiteDesc.h>

#include <testngppst/listener/TestResultCollector.h>

#include <testngppst/runner/TestSuiteRunner.h>
#include <testngppst/runner/TestFilter.h>
#include <testngppst/runner/TestFixtureRunner.h>
#include <testngppst/runner/TestSuiteContext.h>

TESTNGPPST_NS_START

/////////////////////////////////////////////////////////////////
struct TestSuiteRunnerImpl 
{
   TestSuiteRunnerImpl( TestFixtureRunner* runner
                      , TestResultCollector* collector)
      : fixtureRunner(runner)
      , resultCollector(collector)
   {}

   ~TestSuiteRunnerImpl()
   {
   }

   void runAllFixtures(TestSuiteContext* suite, const TestCaseFilter* filter);

	void run(TestSuiteContext* suite, const TestCaseFilter* filter);

   TestFixtureRunner* fixtureRunner;     // X
   TestResultCollector* resultCollector; // X
};

/////////////////////////////////////////////////////////////////
TestSuiteRunner::TestSuiteRunner
   ( TestFixtureRunner* runner
   , TestResultCollector* collector)
	: This(new TestSuiteRunnerImpl(runner, collector))
{
}

/////////////////////////////////////////////////////////////////
TestSuiteRunner::~TestSuiteRunner()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
void
TestSuiteRunnerImpl::
runAllFixtures(TestSuiteContext* suite, const TestCaseFilter* filter)
{
   for(unsigned int i=0; i<suite->numberOfFixtures(); i++)
   {
      TestFixtureContext* fixture = suite->getFixture(i);

	  fixtureRunner->run(fixture, resultCollector, filter, suite->getSuitePath());
   }
}

/////////////////////////////////////////////////////////////////
void
TestSuiteRunnerImpl::
run(TestSuiteContext* suite, const TestCaseFilter* filter)
{
   resultCollector->startTestSuite(suite->getSuite());
	runAllFixtures(suite, filter);
   resultCollector->endTestSuite(suite->getSuite());
}

/////////////////////////////////////////////////////////////////
void
TestSuiteRunner::
run(TestSuiteContext* suite, const TestCaseFilter* filter)
{
   This->run(suite, filter);
}

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END


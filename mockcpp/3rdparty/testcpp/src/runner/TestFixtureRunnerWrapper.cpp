
#include <testcpp/Error.h>

#include <testcpp/internal/TestFixtureInfoReader.h>
#include <testcpp/internal/TestFixtureDesc.h>

#include <testcpp/runner/TestFixtureRunnerWrapper.h>
#include <testcpp/runner/TestFixtureRunner.h>
#include <testcpp/runner/TestFixtureResultCollector.h>


TESTCPP_NS_START

/////////////////////////////////////////////////////////////////
TestFixtureRunnerWrapper::TestFixtureRunnerWrapper(TestFixtureRunner* runner)
	: fixtureRunner(runner)
{
}

/////////////////////////////////////////////////////////////////
TestFixtureRunnerWrapper::~TestFixtureRunnerWrapper()
{
    delete fixtureRunner;
}

/////////////////////////////////////////////////////////////////
void TestFixtureRunnerWrapper::run(TestFixtureDesc* desc
     , TestFixtureResultCollector* collector)
{
   collector->startTestFixture(desc);

   try{
      fixtureRunner->run(desc, collector);
   }
   catch(Error& e)
   {
      collector->addFixtureError(desc, e.what());
   }
   catch(...)
   {
      collector->addFixtureError(desc, "Unknow Error");
   }

   collector->endTestFixture(desc);
}

TESTCPP_NS_END


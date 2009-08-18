
#include <testcpp/internal/TestSuiteDesc.h>

#include <testcpp/runner/TestSuiteRunner.h>
#include <testcpp/runner/TestSuiteLoader.h>
#include <testcpp/runner/TestFixtureRunner.h>
#include <testcpp/runner/TestSuiteResultCollector.h>
#include <testcpp/runner/TestSuiteDescEntryNameGetter.h>

TESTCPP_NS_START

/////////////////////////////////////////////////////////////////
namespace
{
   const std::string testcppTestSuiteDescGetter("___testcpp_test_suite_desc_getter");
}

/////////////////////////////////////////////////////////////////
struct TestSuiteRunnerImpl : public TestSuiteDescEntryNameGetter
{
   TestSuiteRunnerImpl(TestFixtureRunner* runner, TestSuiteLoader* loader)
		: fixtureRunner(runner), suiteLoader(loader)
   {}

	TestSuiteDesc* load(const std::string& path
         , TestSuiteResultCollector* resultCollector);

	void runAllFixtures(TestSuiteDesc* desc
   		, TestSuiteResultCollector* resultCollector);

	void runAllFixtures(TestSuiteDesc* desc);

	void run(const std::string& path, TestSuiteResultCollector* resultCollector);

   std::string getDescEntryName() const
   { return testcppTestSuiteDescGetter; }

   TestFixtureRunner* fixtureRunner;
   TestSuiteLoader* suiteLoader;
};

/////////////////////////////////////////////////////////////////
TestSuiteRunner::TestSuiteRunner(TestSuiteLoader* loader
   , TestFixtureRunner* runner)
	: This(new TestSuiteRunnerImpl(runner, loader))
{
}

/////////////////////////////////////////////////////////////////
TestSuiteRunner::~TestSuiteRunner()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc*
TestSuiteRunnerImpl::load(const std::string& path
   , TestSuiteResultCollector* resultCollector)
{
   try {
     return suiteLoader->load(path, this);
   }
   catch(std::exception& e)
   {
      resultCollector->addError(e.what());
   }
   catch(...)
   {
      throw;
   }

   return 0;
}

/////////////////////////////////////////////////////////////////
void
TestSuiteRunnerImpl::runAllFixtures(TestSuiteDesc* desc
   , TestSuiteResultCollector* resultCollector)
{
   for(unsigned int i=0; i<desc->getNumberOfTestFixtures(); i++)
   {
      TestFixtureDesc* fixture = desc->getTestFixture(i);
      fixtureRunner->run(fixture, resultCollector);
   }
}

/////////////////////////////////////////////////////////////////
void
TestSuiteRunnerImpl::run(const std::string& path
   , TestSuiteResultCollector* resultCollector)
{
   TestSuiteDesc* desc = load(path, resultCollector);
   if(desc == 0)
   {
      return;
   }

   resultCollector->startTestSuite(desc);
	runAllFixtures(desc, resultCollector);
   resultCollector->endTestSuite(desc);

   suiteLoader->unload();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteRunner::run(const std::string& path
   , TestSuiteResultCollector* resultCollector)
{
   This->run(path, resultCollector);
}

/////////////////////////////////////////////////////////////////

TESTCPP_NS_END


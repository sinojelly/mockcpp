
#include <testngppst/comm/ExceptionKeywords.h>

#include <testngppst/utils/InternalError.h>

#include <testngppst/internal/Error.h>

#include <testngppst/internal/TestFixtureInfoReader.h>
#include <testngppst/internal/TestFixtureDesc.h>

#include <testngppst/listener/TestFixtureResultCollector.h>

#include <testngppst/runner/TestFixtureRunner.h>
#include <testngppst/runner/TestHierarchyRunner.h>
#include <testngppst/runner/TestHierarchyHandler.h>

#include <testngppst/runner/TestCaseFilter.h>
#include <testngppst/runner/FixtureTagsFilter.h>
#include <testngppst/runner/TestFixtureContext.h>


TESTNGPPST_NS_START

/////////////////////////////////////////////////////////////////
struct TestFixtureRunnerImpl
{
   TestFixtureRunnerImpl(TestHierarchyRunner* runner);
   ~TestFixtureRunnerImpl();

   void run( TestFixtureContext* context
           , TestFixtureResultCollector* collector
           , const TestCaseFilter* filter
		   , const std::string& );

   TestHierarchyRunner* hierarchyRunner; // Y
};

/////////////////////////////////////////////////////////////////
TestFixtureRunnerImpl::
TestFixtureRunnerImpl(TestHierarchyRunner* runner)
	: hierarchyRunner(runner)
{
}

/////////////////////////////////////////////////////////////////
TestFixtureRunnerImpl::
~TestFixtureRunnerImpl()
{
   delete hierarchyRunner;
}

/////////////////////////////////////////////////////////////////
TestFixtureRunner::
TestFixtureRunner(TestHierarchyRunner* runner)
	: This(new TestFixtureRunnerImpl(runner))
{
}

/////////////////////////////////////////////////////////////////
TestFixtureRunner::~TestFixtureRunner()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
void TestFixtureRunnerImpl::
run( TestFixtureContext* context
   , TestFixtureResultCollector* collector
   , const TestCaseFilter* filter
   , const std::string& suitePath)
{
   TestHierarchyHandler* handler = \
      new TestHierarchyHandler
	     ( suitePath
		 , context->getFixture()
		 , filter
		 , context->getTagsFilter()
		 , collector);

   collector->startTestFixture(context->getFixture());

   __TESTNGPPST_TRY
   {
      hierarchyRunner->run(handler, collector);
   }
   __TESTNGPPST_CATCH(Error& e)
   {
      collector->addFixtureError(context->getFixture(), e.what());
   }
   __TESTNGPPST_CATCH(std::exception& e)
   {
       collector->addFixtureError(context->getFixture(), e.what());
   }   
   __TESTNGPPST_CATCH_ALL
   {
      collector->addFixtureError(context->getFixture(), "Unknown Error");
   }
   __TESTNGPPST_END_TRY

   collector->endTestFixture(context->getFixture());

   delete handler;
}


/////////////////////////////////////////////////////////////////
void TestFixtureRunner::
run( TestFixtureContext* context
   , TestFixtureResultCollector* collector
   , const TestCaseFilter* filter
   , const std::string& suitePath)
{
   return This->run(context, collector, filter, suitePath);
}

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END


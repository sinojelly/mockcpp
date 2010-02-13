
#if defined(_MSC_VER)
#include <windows.h>
#include <testngpp/win32/die.h>
#endif

#include <testngpp/runner/TestCaseRunnerDieHandler.h>
#include <testngpp/runner/SimpleTestCaseRunner.h>
#include <testngpp/runner/TestCaseResultCollector.h>
#include <testngpp/internal/TestCase.h>
#include <testngpp/internal/TestFixtureDesc.h>

TESTNGPP_NS_START

#define __RUN(block) try block \
   catch(AssertionFailure& failure) \
   { \
      if(!(reportSuccess || hasFailure)) collector->startTestCase(testcase); \
      collector->addCaseFailure(testcase, failure); \
      hasFailure = true; \
   } \
   catch(std::exception& e) \
   { \
      if(!(reportSuccess || hasFailure)) collector->startTestCase(testcase); \
      collector->addCaseError(testcase, e.what()); \
      hasFailure = true; \
   } \
   catch(...) \
   { \
      if(!(reportSuccess || hasFailure)) collector->startTestCase(testcase); \
      collector->addCaseError(testcase, "Unknown Exception"); \
      hasFailure = true; \
   }

namespace
{
bool runTest
      ( TestCase* testcase
      , TestCaseResultCollector* collector
      , bool reportSuccess)
{
   bool hasFailure = false;

   __RUN({
      testcase->setUp();
      testcase->run(true);
   });

   __RUN({
      testcase->tearDown();
   });

   return !hasFailure;
}

#if defined(_MSC_VER)
int tryToRunTest
      ( TestCase* testcase
      , TestCaseResultCollector* collector
      , bool reportSuccess)
{

	__try {
		if(!runTest(testcase, collector, reportSuccess))
		{
			return 1;
		}
	}__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return -1;
	}

	return 0;
}
#endif
}

//////////////////////////////////////////
bool SimpleTestCaseRunner::run
      ( TestCase* testcase
      , TestCaseResultCollector* collector
      , bool reportSuccess)
{
   bool hasFailure = false;

   if(reportSuccess)
   {
      collector->startTestCase(testcase);
   }

#if defined(_MSC_VER)
   int result = tryToRunTest
	   ( testcase
	   , collector
	   , reportSuccess);

   if(result < 0 && handler != 0)
   {
	   handler->die(testcase, collector);
   }

   hasFailure = (result==0?false:true);
#else
   hasFailure = !runTest(testcase, collector, reportSuccess);
#endif

   if(hasFailure || reportSuccess)
   {
      collector->endTestCase(testcase);
   }

   return !hasFailure;
}

TESTNGPP_NS_END


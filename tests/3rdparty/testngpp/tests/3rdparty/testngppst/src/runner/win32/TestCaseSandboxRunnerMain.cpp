
#include <string>
#include <iostream>

#include <windows.h>

#include <testngppst/comm/ExceptionKeywords.h>
#include <testngppst/comm/Win32PipeWrittableChannel.h>
#include <testngppst/runner/TestCaseSandboxResultReporter.h>
#include <testngppst/runner/loaders/ModuleTestSuiteLoaderFactory.h>
#include <testngppst/runner/TestFilter.h>
#include <testngppst/runner/TestFilterFactory.h>
#include <testngppst/runner/TagsFilters.h>
#include <testngppst/runner/TagsParser.h>
#include <testngppst/runner/TestRunnerContext.h>
#include <testngppst/runner/TestSuiteRunner.h>
#include <testngppst/runner/TestFixtureRunner.h>
#include <testngppst/runner/TestFixtureRunnerFactory.h>
#include <testngppst/win32/Win32TestCaseRunnerResultReporter.h>

void usage()
{
    std::cerr << "Usage: testngppst-win32-testcase-runner.exe testsuite fixture testcase" << std::endl;
	ExitProcess(1);
}

TESTNGPPST_NS::TestCaseRunnerResultReporter* 
createCollector(HANDLE hWrite, HANDLE hSemaphore)
{
   if(hWrite == 0)
   {
	   hWrite = GetStdHandle(STD_OUTPUT_HANDLE);  
	   if (hWrite == INVALID_HANDLE_VALUE)
	   {		
		  ExitProcess(1); 
	   }
   }
   
   return new TESTNGPPST_NS::TestCaseRunnerResultReporter(hSemaphore,
	         new TESTNGPPST_NS::TestCaseSandboxResultReporter(
	            new TESTNGPPST_NS::Win32PipeWrittableChannel(hWrite)));
}

const TESTNGPPST_NS::TestFilter*
createFilter
      ( const std::string& fixtureName
	  , const std::string& testcaseName)
{
	TESTNGPPST_NS::StringList filterPattern;
	filterPattern.add(fixtureName + ":" + testcaseName);
	return TESTNGPPST_NS::TestFilterFactory::getFilter(filterPattern);
}

int runTest
      ( TESTNGPPST_NS::TestCaseRunnerResultReporter* collector
      , const std::string& suiteName
	  , const std::string& fixtureName
	  , const std::string& testcaseName)
{
	std::cout << "testcase name : " << testcaseName << std::endl;
	const TESTNGPPST_NS::TestFilter* filter = createFilter(fixtureName, testcaseName);
	TESTNGPPST_NS::TagsFilters* tagsFilter = TESTNGPPST_NS::TagsParser::parse("*");
    TESTNGPPST_NS::TestFixtureRunner* fixtureRunner = 0;
	TESTNGPPST_NS::TestSuiteRunner* suiteRunner = 0;
	TESTNGPPST_NS::TestRunnerContext* context = 0;

	TESTNGPPST_NS::StringList suites;
	suites.add(suiteName);

	int result = 0;

	__TESTNGPPST_TRY

	context = new TESTNGPPST_NS::TestRunnerContext
            ( suites
            , collector
            , tagsFilter
            , filter);

	fixtureRunner = TESTNGPPST_NS::TestFixtureRunnerFactory::createInstance(false, 1);
	suiteRunner = new TESTNGPPST_NS::TestSuiteRunner(fixtureRunner, collector);

	if(!tagsFilter->startOnNext())
	{
		std::cerr << "internal error" << std::endl;
	}
	////////////////////////////////////////////////////
    suiteRunner->run(context->getSuite(0), filter);
	////////////////////////////////////////////////////

	__TESTNGPPST_CATCH_ALL
        
		result = -1;

	__TESTNGPPST_FINALLY
	
		if(context != 0)
		{
			delete context;
		}

		if(suiteRunner != 0)
		{
			delete suiteRunner;
		}
		if(fixtureRunner != 0)
		{
			delete fixtureRunner;
		}
		
	__TESTNGPPST_DONE

	delete tagsFilter;
	TESTNGPPST_NS::TestFilterFactory::returnFilter(filter);

	return result;
}

int main(int argc, char* argv[])
{
   if(argc != 6 && argc != 4)
   {
      usage(); 
   }
   
   std::cout << "start to run " << std::endl;
   std::string suite(argv[1]);
   std::string fixture(argv[2]);
   std::string testcase(argv[3]);
   
   HANDLE hWrite = 0;
   HANDLE hSemap = 0;
   
   if(argc == 6)
   {
      hWrite = (HANDLE)atoi(argv[4]);
      hSemap = (HANDLE)atoi(argv[5]);
   }

   return 
	   runTest(createCollector(hWrite, hSemap), suite, fixture, testcase);

}

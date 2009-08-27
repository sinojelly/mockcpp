
#include <iostream>

#include <testcpp/Error.h>

#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestSuiteInfoReader.h>

#include <testcpp/runner/TestResultReporter.h>
#include <testcpp/runner/TestSuiteResultReporter.h>
#include <testcpp/runner/TestCaseResultReporter.h>
#include <testcpp/runner/InternalError.h>

#include <StdoutTestListener.h>

TESTCPP_NS_START

namespace
{
  const char vt100_red[]    = "\033[31;1m";       //red
  const char vt100_green[]  = "\033[32;1m";       //green
  const char vt100_yellow[] = "\033[33;1m";       //yellow
  const char vt100_reset[]  = "\033[0m";          //reset
  const char vt100_clear[]  = "\033[2J";          //clear
  const char vt100_home[]   = "\033[0;0H";        //back to left corner
}

struct StdoutTestListenerImpl
{
   StdoutTestListenerImpl(TestResultReporter* reporter
      , TestSuiteResultReporter* suiteReporter
      , TestCaseResultReporter* caseReporter)
      : resultReporter(reporter)
      , suiteResultReporter(suiteReporter)
      , caseResultReporter(caseReporter)
   {}

   TestResultReporter* resultReporter;
   TestSuiteResultReporter* suiteResultReporter;
   TestCaseResultReporter* caseResultReporter;
};

///////////////////////////////////////////////////////////
StdoutTestListener::StdoutTestListener(TestResultReporter* reporter
   , TestSuiteResultReporter* suiteReporter
   , TestCaseResultReporter* caseReporter)
   : This(new StdoutTestListenerImpl(reporter, suiteReporter, caseReporter))
{
}

///////////////////////////////////////////////////////////
StdoutTestListener::~StdoutTestListener()
{
   delete This;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
addCaseCrash(TestCaseInfoReader* testcase)
{
   std::cout << "C";
   std::cout.flush();

   std::cerr << std::endl
             << testcase->getFileName() 
             << ":" 
             << testcase->getLineOfFile() 
             << ":" 
             << testcase->getNameOfFixture() 
             << ":" 
             << testcase->getName()
             << ": test case crashed unexpectedly." 
             << std::endl;
}
///////////////////////////////////////////////////////////
void StdoutTestListener::
addCaseError(TestCaseInfoReader* testcase, const std::string& msg)
{
   std::cerr << std::endl
             << testcase->getFileName() 
             << ":" 
             << testcase->getLineOfFile() 
             << ":" 
             << testcase->getNameOfFixture() 
             << ":" 
             << testcase->getName()
             << ": " 
             << msg << std::endl;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
addCaseFailure(TestCaseInfoReader* testcase, const AssertionFailure& failure)
{
   std::cerr << std::endl
             << failure.getFileName()
             << ":"
             << failure.getLineOfFile()
             << ":" 
             << testcase->getNameOfFixture() 
             << ":" 
             << testcase->getName()
             << ": "
             << failure.what()
             << std::endl;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
startTestCase(TestCaseInfoReader*)
{
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
endTestCase(TestCaseInfoReader* testcase)
{
   switch(This->caseResultReporter->getTestCaseResult(testcase))
   {
   case TestCaseResultReporter::SUCCESS:
      std::cout << "."; 
      break;
   case TestCaseResultReporter::FAILED:
      std::cout << "F";
      break;
   case TestCaseResultReporter::ERROR:
      std::cout << "E"; 
      break;
   case TestCaseResultReporter::UNKNOWN:
      throw Error(TESTCPP_INTERNAL_ERROR(3001));
   }
   std::cout.flush();
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
startTestFixture(TestFixtureInfoReader*)
{

}

///////////////////////////////////////////////////////////
void StdoutTestListener::
endTestFixture(TestFixtureInfoReader*)
{
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
addFixtureError(TestFixtureInfoReader*, const std::string& msg)
{
   std::cerr << std::endl
             << "fixture error: " 
             << msg << std::endl;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
addFixtureFailure(TestFixtureInfoReader*, const AssertionFailure& failure)
{
   std::cerr << std::endl
             << "fixture failure:" 
             << failure.what() << std::endl;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
startTestSuite(TestSuiteInfoReader* suite)
{
#if 0
   std::cout << suite->getName() << std::endl;
#endif
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
endTestSuite(TestSuiteInfoReader* suite)
{
#if 0
   if(suite == 0)
   {
      return;
   }

   TestSuiteResultReporter* reporter = This->suiteResultReporter;

   unsigned int successCases = reporter->getNumberOfSuccessfulTestCases(suite);

   int successRate = 0;
   if(reporter->getNumberOfTestCases(suite) != 0)
   {
      successRate = int(successCases*100/reporter->getNumberOfTestCases(suite)); 
   }

   std::cout << std::endl
             << " success: " << successCases
             << " failed: " << reporter->getNumberOfFailedTestCases(suite)
             << " error: "  << reporter->getNumberOfErrorTestCases(suite)
             << " crash: "  << reporter->getNumberOfCrashedTestCases(suite) << std::endl
             << " success rate: " << successRate << "%"
             << std::endl
             << "======================================"
             << std::endl;
#endif

}

///////////////////////////////////////////////////////////
void StdoutTestListener::
addSuiteError(TestSuiteInfoReader*, const std::string& msg )
{
   std::cerr << std::endl
             << "suite error: " 
             << msg
             << std::endl;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::startTest()
{
}

///////////////////////////////////////////////////////////
void StdoutTestListener::endTest()
{


   if(This->resultReporter->getNumberOfTestCases() == 0)
   {
      std::cerr << "No test to run!" << std::endl;
   }


   if(This->resultReporter->getNumberOfUnloadableSuites() == 0 &&
         This->resultReporter->getNumberOfUnsuccessfulTestCases() == 0)
   {
      std::cout << "(" << This->resultReporter->getNumberOfTestCases()
                << " cases) OK!" << std::endl;
      return ;
   }



   std::cout << std::endl;

   if(This->resultReporter->getNumberOfUnloadableSuites() > 0)
   {
      unsigned int totalSuites = This->resultReporter->getNumberOfLoadedSuites() 
                               + This->resultReporter->getNumberOfUnloadableSuites();

      unsigned int rate = (unsigned int)(100*This->resultReporter->getNumberOfLoadedSuites()/totalSuites);

      std::cout << " loaded suites: " << This->resultReporter->getNumberOfLoadedSuites()
                << " unloadable suites: " << This->resultReporter->getNumberOfUnloadableSuites()
                << std::endl
                << " load success rate: " << rate << "%"
                << std::endl;
   }

   if(This->resultReporter->getNumberOfUnsuccessfulTestCases() > 0)
   {
      unsigned int successCases = This->resultReporter->getNumberOfSuccessfulTestCases();
      unsigned int rate = int(successCases*100/This->resultReporter->getNumberOfTestCases()); 

      std::cout << " success: " << successCases;

      if(This->resultReporter->getNumberOfFailedTestCases() > 0)
      {
         std::cout << " failed: " << This->resultReporter->getNumberOfFailedTestCases();
      }

      if(This->resultReporter->getNumberOfErrorTestCases() > 0)
      {
         std::cout << " error: "  << This->resultReporter->getNumberOfErrorTestCases();
      }

      if(This->resultReporter->getNumberOfCrashedTestCases() > 0)
      {
         std::cout << " crashed: "  << This->resultReporter->getNumberOfCrashedTestCases();
      }
      std::cout << std::endl 
                << " success rate: " << rate << '%' << std::endl;
   }
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
addError(const std::string& msg)
{
   std::cerr << std::endl
             << "error: " 
             << msg
             << std::endl;
}

TESTCPP_NS_END

///////////////////////////////////////////////////////////
USING_TESTCPP_NS
///////////////////////////////////////////////////////////
extern "C"
TestListener*
testcppstdoutlistener_create_instance(
   TestResultReporter* resultReporter,
   TestSuiteResultReporter* suiteReporter,
   TestCaseResultReporter* caseResultReporter)
{
    return new StdoutTestListener(resultReporter, suiteReporter, caseResultReporter);
}

///////////////////////////////////////////////////////////
extern "C"
void
testcppstdoutlistener_destroy_instance(TestListener* instance)
{
    delete instance;
}

///////////////////////////////////////////////////////////

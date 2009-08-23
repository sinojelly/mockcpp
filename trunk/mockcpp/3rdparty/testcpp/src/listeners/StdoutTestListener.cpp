
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
   std::cout << suite->getName() 
             << ":"
             << " running "
             << suite->getNumberOfTestCases()
             << " test cases"
             << std::endl;
}

///////////////////////////////////////////////////////////
void StdoutTestListener::
endTestSuite(TestSuiteInfoReader* suite)
{
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
   unsigned int successCases = This->resultReporter->getNumberOfSuccessfulTestCases();

   int successRate = 0;
   if(This->resultReporter->getNumberOfTestCases() != 0)
   {
      successRate = int(successCases*100/This->resultReporter->getNumberOfTestCases()); 
   }

   std::cout << std::endl
             << " loaded suites: " << This->resultReporter->getNumberOfLoadedSuites()
             << " unloadable suites: " << This->resultReporter->getNumberOfUnloadableSuites()
             << std::endl
             << " success: " << successCases
             << " failed: " << This->resultReporter->getNumberOfFailedTestCases()
             << " error: "  << This->resultReporter->getNumberOfErrorTestCases()
             << " crash: "  << This->resultReporter->getNumberOfCrashedTestCases() << std::endl
             << " success rate: " << successRate << "%"
             << std::endl;
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

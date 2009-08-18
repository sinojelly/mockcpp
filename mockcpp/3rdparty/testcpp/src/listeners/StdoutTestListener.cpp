
#include <iostream>

#include <testcpp/Error.h>

#include <testcpp/internal/TestCaseInfoReader.h>
#include <testcpp/internal/TestSuiteInfoReader.h>

#include <testcpp/runner/TestResultReporter.h>
#include <testcpp/runner/TestCaseResultReporter.h>
#include <testcpp/runner/InternalError.h>

#include <StdoutTestListener.h>

TESTCPP_NS_START

struct StdoutTestListenerImpl
{
   StdoutTestListenerImpl(TestResultReporter* reporter
      , TestCaseResultReporter* caseReporter)
      : resultReporter(reporter)
      , caseResultReporter(caseReporter)
   {}

   TestResultReporter* resultReporter;
   TestCaseResultReporter* caseResultReporter;
};

///////////////////////////////////////////////////////////
StdoutTestListener::StdoutTestListener(TestResultReporter* reporter
   , TestCaseResultReporter* caseReporter)
   : This(new StdoutTestListenerImpl(reporter, caseReporter))
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

   unsigned int successCases = This->resultReporter->getNumberOfSuccessfulTestCases();
   std::cout << std::endl
             << " success: " << successCases
             << " failed: " << This->resultReporter->getNumberOfFailedTestCases()
             << " error: "  << This->resultReporter->getNumberOfErrorTestCases()
             << " crash: "  << This->resultReporter->getNumberOfCrashedTestCases() << std::endl
             << " success rate: " << int(successCases*100/This->resultReporter->getNumberOfTestCases()) << "%"
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
   TestCaseResultReporter* caseResultReporter)
{
    return new StdoutTestListener(resultReporter, caseResultReporter);
}

///////////////////////////////////////////////////////////
extern "C"
void
testcppstdoutlistener_destroy_instance(TestListener* instance)
{
    delete instance;
}

///////////////////////////////////////////////////////////

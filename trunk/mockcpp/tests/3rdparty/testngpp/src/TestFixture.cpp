
#include <testngpp/TestFixture.h>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/Warning.h>
#include <testngpp/internal/Info.h>

#include <testngpp/listener/TestCaseResultCollector.h>

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////////////////
void TestFixture::
reportInfo
      ( const char* file
      , unsigned int line
      , const std::string& info)
{
   if(collector == 0 || testcase == 0) return;
   collector->addCaseInfo(testcase, Info(file, line, info));
}

//////////////////////////////////////////////////////////////////////////
void TestFixture::
reportWarning
      ( const char *file
      , unsigned int line
      , const std::string & warning)
{
   if(collector == 0 || testcase == 0) return;
   collector->addCaseWarning(testcase, Warning(file, line, warning));
}

void TestFixture::
reportFailure(const char* file, unsigned int line, const std::string& what)
{
   if(collector == 0 || testcase == 0) return;

   AssertionFailure failure(file, line, what);

   collector->addCaseFailure(testcase, failure);

   throw failure;
}
//////////////////////////////////////////////////////////////////////////
void TestFixture::
setCurrentTestCase(const TestCaseInfoReader* currentCase, TestCaseResultCollector* resultCollector)
{
   testcase = currentCase;
   collector = resultCollector;
}

TESTNGPP_NS_END







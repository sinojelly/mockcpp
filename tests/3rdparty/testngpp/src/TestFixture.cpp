
#include <testngpp/TestFixture.h>
#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/Warning.h>
#include <testngpp/internal/Info.h>
#include <testngpp/internal/MemChecker.h>

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
reportFailure(const char* file, unsigned int line, const std::string& what, bool throwException)
{
   if(collector == 0 || testcase == 0) return;

   AssertionFailure failure(file, line, what);

   collector->addCaseFailure(testcase, failure);

   if(throwException) throw failure;
}
//////////////////////////////////////////////////////////////////////////
void TestFixture::
reportMemLeakInfo
      ( const char* file
      , unsigned int line
      , const std::string& info)
{
   if(memLeakCollector == 0 || testcase == 0) return;
   memLeakCollector->addCaseInfo(testcase, Info(file, line, info));
}

void TestFixture::
reportMemLeakFailure(const char* file, unsigned int line, const std::string& what, bool throwException)
{
   if(memLeakCollector == 0 || testcase == 0) return;

   AssertionFailure failure(file, line, what);

   memLeakCollector->addCaseFailure(testcase, failure);

   if(throwException) throw failure;
}



//////////////////////////////////////////////////////////////////////////
void TestFixture::
setCurrentTestCase( const TestCaseInfoReader* currentCase
	                  , TestCaseResultCollector* resultCollector
	                  , TestCaseResultCollector* memLeakCollector
	                  , MemChecker* memChecker)
{
   this->testcase = currentCase;
   this->collector = resultCollector;
   this->memLeakCollector = memLeakCollector;
   this->memChecker = memChecker;
}

//////////////////////////////////////////////////////////////////////////
void TestFixture::
startMemChecker()
{
   memChecker->start();
}

void TestFixture::
verifyMemChecker()
{
   memChecker->verify();
}


TESTNGPP_NS_END







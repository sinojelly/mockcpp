
#include <testngppst/runner/SimpleTestCaseRunner.h>
#include <testngppst/runner/TestCaseRunnerFactory.h>

TESTNGPPST_NS_START
////////////////////////////////////////////////////////
namespace
{
   unsigned int ref = 0;

   TestCaseRunner* caseRunner = 0;
}

TestCaseRunner*
TestCaseRunnerFactory::createInstance()
{
   if(caseRunner == 0)
   {
      caseRunner = new SimpleTestCaseRunner();
      ref = 1;
   }
   else
   {
      ref++;
   }

   return caseRunner;
}

void 
TestCaseRunnerFactory::releaseInstance(TestCaseRunner* runner)
{
   if(ref == 0)
   {
      return;
   }

   if(--ref == 0)
   {
      delete caseRunner;
      caseRunner = 0;
   }
}

TESTNGPPST_NS_END


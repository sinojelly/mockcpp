
#include <testcpp/runner/TestFixtureRunnerWrapper.h>
#include <testcpp/runner/TestFixtureSandboxRunner.h>
#include <testcpp/runner/SimpleTestCaseRunner.h>
#include <testcpp/runner/TestFixtureSandboxRunnerFactory.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
namespace
{
   unsigned int ref = 0;

   TestCaseRunner* caseRunner = 0;

   TestCaseRunner* createTestCaseRunner()
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

   void freeTestCaseRunner()
   {
      if(ref == 0)
      {
         return;
      }

      if(--ref == 0)
      {
         delete caseRunner;
      }
   }
}


////////////////////////////////////////////////////////
TestFixtureRunner*
TestFixtureSandboxRunnerFactory::
createInstance(unsigned int maxConcurrent)
{
   if(maxConcurrent == 0)
   {
      maxConcurrent = 1;
   }

   return new TestFixtureRunnerWrapper( \
                  new TestFixtureSandboxRunner( \
                     maxConcurrent, createTestCaseRunner()));
}

////////////////////////////////////////////////////////
void 
TestFixtureSandboxRunnerFactory::
destroyInstance(TestFixtureRunner* instance)
{
   if(instance == 0)
   {
      return;
   }

   delete instance;

   freeTestCaseRunner();
}

////////////////////////////////////////////////////////

TESTCPP_NS_END

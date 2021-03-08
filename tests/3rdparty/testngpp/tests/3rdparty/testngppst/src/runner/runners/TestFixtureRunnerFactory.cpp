
#include <testngppst/runner/TestFixtureRunner.h>
#include <testngppst/runner/SimpleTestHierarchyRunner.h>
#include <testngppst/runner/TestCaseRunnerFactory.h>
#include <testngppst/runner/TestFixtureRunnerFactory.h>

#if !defined(TESTNGPPST_DISABLE_SANDBOX) || !TESTNGPPST_DISABLE_SANDBOX
#if defined(_MSC_VER)
#include <testngppst/win32/Win32TestHierarchySandboxRunner.h>
#else
#include <testngppst/runner/TestHierarchySandboxRunner.h>
#endif
#endif

TESTNGPPST_NS_START

namespace
{

#if !defined(TESTNGPPST_DISABLE_SANDBOX) || !TESTNGPPST_DISABLE_SANDBOX
   TestFixtureRunner*
   createSandboxInstance(unsigned int maxConcurrent)
   {
      if(maxConcurrent == 0)
      {
         maxConcurrent = 1;
      }

      return new TestFixtureRunner( 
#if defined(_MSC_VER)
		          new Win32TestHierarchySandboxRunner(
#else
		          new TestHierarchySandboxRunner( 
#endif
                     maxConcurrent, TestCaseRunnerFactory::createInstance()));
   }
#endif

   TestFixtureRunner*
   createSimpleInstance()
   {
      return new TestFixtureRunner( \
                  new SimpleTestHierarchyRunner( \
				  TestCaseRunnerFactory::createInstance()));
   }
}


////////////////////////////////////////////////////////
TestFixtureRunner*
TestFixtureRunnerFactory::
createInstance(bool useSandbox, unsigned int maxConcurrent)
{
#if defined(TESTNGPPST_DISABLE_SANDBOX) && TESTNGPPST_DISABLE_SANDBOX
   return createSimpleInstance();
#else
   return useSandbox? createSandboxInstance(maxConcurrent) :
      createSimpleInstance();
#endif
}

////////////////////////////////////////////////////////
void 
TestFixtureRunnerFactory::
destroyInstance(TestFixtureRunner* instance)
{
   if(instance == 0)
   {
      return;
   }

   delete instance;

   TestCaseRunnerFactory::releaseInstance(0);
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END

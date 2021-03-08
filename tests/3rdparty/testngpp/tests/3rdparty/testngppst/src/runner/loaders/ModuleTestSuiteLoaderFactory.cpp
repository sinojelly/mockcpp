

#include <testngppst/internal/Error.h>
#include <testngppst/runner/loaders/ModuleTestSuiteLoaderFactory.h>
#include <testngppst/runner/loaders/ModuleTestSuiteLoader.h>
#include <testngppst/runner/loaders/ModuleLoaderFactory.h>

TESTNGPPST_NS_START

/////////////////////////////////////////////////////////////////
TestSuiteLoader* 
ModuleTestSuiteLoaderFactory::create()
{
   return new ModuleTestSuiteLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END


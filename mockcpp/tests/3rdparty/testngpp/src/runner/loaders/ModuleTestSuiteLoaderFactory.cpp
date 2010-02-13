
#include <testngpp/Error.h>
#include <testngpp/ExceptionKeywords.h>

#include <testngpp/runner/ModuleTestSuiteLoaderFactory.h>
#include <testngpp/runner/ModuleTestSuiteLoader.h>
#include <testngpp/runner/ModuleLoaderFactory.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
TestSuiteLoader* 
ModuleTestSuiteLoaderFactory::create()
{
   return new ModuleTestSuiteLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END


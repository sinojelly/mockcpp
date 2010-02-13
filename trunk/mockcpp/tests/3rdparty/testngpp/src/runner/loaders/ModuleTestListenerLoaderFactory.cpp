
#include <testngpp/Error.h>
#include <testngpp/ExceptionKeywords.h>

#include <testngpp/runner/ModuleTestListenerLoaderFactory.h>
#include <testngpp/runner/ModuleTestListenerLoader.h>
#include <testngpp/runner/ModuleLoaderFactory.h>

TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
TestListenerLoader* 
ModuleTestListenerLoaderFactory::create()
{
   return new ModuleTestListenerLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPP_NS_END


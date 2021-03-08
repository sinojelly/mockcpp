
#include <testngppst/runner/loaders/ModuleTestListenerLoaderFactory.h>
#include <testngppst/runner/loaders/ModuleTestListenerLoader.h>
#include <testngppst/runner/loaders/ModuleLoaderFactory.h>

TESTNGPPST_NS_START

/////////////////////////////////////////////////////////////////
TestListenerLoader* 
ModuleTestListenerLoaderFactory::create()
{
   return new ModuleTestListenerLoader(ModuleLoaderFactory::create());
}

/////////////////////////////////////////////////////////////////

TESTNGPPST_NS_END


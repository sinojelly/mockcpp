
#include <testngppst/runner/loaders/ModuleLoader.h>
#include <testngppst/runner/loaders/ModuleLoaderFactory.h>

#include <testngppst/runner/loaders/Win32DllModuleLoader.h>


TESTNGPPST_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new Win32DllModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END


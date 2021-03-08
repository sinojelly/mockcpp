
#include <testngppst/runner/loaders/ModuleLoader.h>
#include <testngppst/runner/loaders/ModuleLoaderFactory.h>

#include <testngppst/runner/loaders/DLModuleLoader.h>

TESTNGPPST_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new DLModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END


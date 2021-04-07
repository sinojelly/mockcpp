
#include <testngppst/runner/loaders/ModuleLoader.h>
#include <testngppst/runner/loaders/ModuleLoaderFactory.h>

#include <testngppst/runner/loaders/LTModuleLoader.h>

TESTNGPPST_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new LTModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END



#include <testngppst/runner/ModuleLoader.h>
#include <testngppst/runner/ModuleLoaderFactory.h>

#include <testngppst/runner/LTModuleLoader.h>

TESTNGPPST_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new LTModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPPST_NS_END



#include <testngpp/runner/ModuleLoader.h>
#include <testngpp/runner/ModuleLoaderFactory.h>

#include <testngpp/runner/DLModuleLoader.h>

TESTNGPP_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new DLModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END


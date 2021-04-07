
#include <testngpp/runner/loaders/ModuleLoader.h>
#include <testngpp/runner/loaders/ModuleLoaderFactory.h>

#include <testngpp/runner/loaders/LTModuleLoader.h>

TESTNGPP_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new LTModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END


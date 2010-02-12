
#include <testngpp/runner/ModuleLoader.h>
#include <testngpp/runner/ModuleLoaderFactory.h>

#include <testngpp/runner/Win32DllModuleLoader.h>


TESTNGPP_NS_START


////////////////////////////////////////////////////////
ModuleLoader*
ModuleLoaderFactory::create()
{
    return new Win32DllModuleLoader();
}

////////////////////////////////////////////////////////

TESTNGPP_NS_END


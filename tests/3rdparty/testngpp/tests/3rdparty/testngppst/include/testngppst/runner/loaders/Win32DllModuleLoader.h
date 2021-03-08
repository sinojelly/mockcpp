
#ifndef __TESTNGPPST_WIN32_DLL_MODULE_LOADER_H
#define __TESTNGPPST_WIN32_DLL_MODULE_LOADER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/loaders/ModuleLoader.h>

TESTNGPPST_NS_START

struct Win32DllModuleLoaderImpl;

struct Win32DllModuleLoader : public ModuleLoader
{
   Win32DllModuleLoader();
   ~Win32DllModuleLoader(); 

	void load( const StringList& searchingPaths
            , const std::string& modulePath);

   void unload();

   void* findSymbol(const std::string& symbol);

private:

   Win32DllModuleLoaderImpl* This;
};

TESTNGPPST_NS_END

#endif


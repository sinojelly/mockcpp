
#ifndef __TESTNGPPST_DL_MODULE_LOADER_H
#define __TESTNGPPST_DL_MODULE_LOADER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/loaders/ModuleLoader.h>

TESTNGPPST_NS_START

struct DLModuleLoaderImpl;

struct DLModuleLoader : public ModuleLoader
{
   DLModuleLoader();
   ~DLModuleLoader(); 

	void load( const StringList& searchingPaths \
            , const std::string& modulePath);
   void unload();

   void* findSymbol(const std::string& symbol);

private:

   DLModuleLoaderImpl* This;
};

TESTNGPPST_NS_END

#endif


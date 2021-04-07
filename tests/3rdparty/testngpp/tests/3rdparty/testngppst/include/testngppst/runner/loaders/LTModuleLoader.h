
#ifndef __TESTNGPPST_LT_MODULE_LOADER_H
#define __TESTNGPPST_LT_MODULE_LOADER_H

#include <testngppst/testngppst.h>
#include <testngppst/runner/loaders/ModuleLoader.h>


TESTNGPPST_NS_START

struct LTModuleLoaderImpl;

struct LTModuleLoader : public ModuleLoader
{
   LTModuleLoader();

   ~LTModuleLoader(); 

   void load( const StringList& searchingPaths \
            , const std::string& modulePath);
   void unload();

   void* findSymbol(const std::string& symbol);

private:

   LTModuleLoaderImpl* This;
};

TESTNGPPST_NS_END

#endif


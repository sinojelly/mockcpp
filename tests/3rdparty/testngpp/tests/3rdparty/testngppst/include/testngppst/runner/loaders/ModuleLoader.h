
#ifndef __TESTNGPPST_MODULE_LOADER_H
#define __TESTNGPPST_MODULE_LOADER_H

#include <testngppst/testngppst.h>

#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct ModuleLoader
{
	virtual void load( const StringList& searchingPaths
                    , const std::string& modulePath) = 0;

   virtual void unload() = 0;

   virtual void* findSymbol(const std::string& symbol) = 0;

   virtual ~ModuleLoader() {}
};

TESTNGPPST_NS_END

#endif


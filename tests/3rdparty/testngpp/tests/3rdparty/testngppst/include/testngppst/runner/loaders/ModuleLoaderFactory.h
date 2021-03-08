
#ifndef __TESTNGPPST_MODULE_LOADER_FACTORY_H
#define __TESTNGPPST_MODULE_LOADER_FACTORY_H

#include <testngppst/testngppst.h>


TESTNGPPST_NS_START

struct ModuleLoader;

struct ModuleLoaderFactory
{
    static ModuleLoader* create();
};

TESTNGPPST_NS_END

#endif



#ifndef __TESTNGPPST_MODULE_LISTENER_LOADER_FACTORY_H
#define __TESTNGPPST_MODULE_LISTENER_LOADER_FACTORY_H

#include <testngppst/testngppst.h>

#include <testngppst/runner/loaders/TestListenerLoaderFactory.h>

TESTNGPPST_NS_START

struct ModuleTestListenerLoaderFactory
   : public TestListenerLoaderFactory
{
   TestListenerLoader* create();
};

TESTNGPPST_NS_END

#endif


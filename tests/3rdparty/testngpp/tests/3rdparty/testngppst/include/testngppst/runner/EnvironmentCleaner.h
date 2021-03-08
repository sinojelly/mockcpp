
#ifndef __TESTNGPPST_ENVIRONMENT_CLEANER_H
#define __TESTNGPPST_ENVIRONMENT_CLEANER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct EnvironmentCleaner
{
   virtual void cleanUp() = 0;

   virtual ~EnvironmentCleaner() {}
};

TESTNGPPST_NS_END

#endif

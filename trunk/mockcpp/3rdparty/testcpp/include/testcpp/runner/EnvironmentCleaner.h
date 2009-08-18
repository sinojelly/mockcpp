
#ifndef __TESTCPP_ENVIRONMENT_CLEANER_H
#define __TESTCPP_ENVIRONMENT_CLEANER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct EnvironmentCleaner
{
   virtual void cleanUp() = 0;

   virtual ~EnvironmentCleaner() {}
};

TESTCPP_NS_END

#endif

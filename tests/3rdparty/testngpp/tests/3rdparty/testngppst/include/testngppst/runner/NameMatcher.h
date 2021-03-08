#ifndef __TESTNGPPST_NAME_MATCHER_H
#define __TESTNGPPST_NAME_MATCHER_H

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////
struct NameMatcher
{
   virtual bool matches(const std::string& name) const = 0;

   virtual std::string getPattern() const = 0;
   
   virtual ~NameMatcher() {}
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif


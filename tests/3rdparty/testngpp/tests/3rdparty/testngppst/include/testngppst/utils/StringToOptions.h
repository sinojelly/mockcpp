
#ifndef __TESTNGPPST_STRING_TO_OPTIONS_H
#define __TESTNGPPST_STRING_TO_OPTIONS_H

#include <list>
#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct StringToOptions
{
   typedef std::pair<int, char**> CArgs;

   static int getNumberOfArgsInString(const std::string& s);
   static CArgs parse(const std::string& s);
};

TESTNGPPST_NS_END

#endif


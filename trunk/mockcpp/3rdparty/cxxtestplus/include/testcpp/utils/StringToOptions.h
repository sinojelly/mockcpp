
#ifndef __TESTCPP_STRING_TO_OPTIONS_H
#define __TESTCPP_STRING_TO_OPTIONS_H

#include <list>
#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct StringToOptions
{
   typedef std::pair<int, char**> CArgs;

   static int getNumberOfArgsInString(const std::string& s);
   static CArgs parse(const std::string& s);
};

TESTCPP_NS_END

#endif


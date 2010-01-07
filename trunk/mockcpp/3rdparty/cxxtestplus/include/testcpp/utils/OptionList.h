
#ifndef __TESTCPP_OPTION_LIST_H
#define __TESTCPP_OPTION_LIST_H

#include <list>
#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct OptionList
{
   typedef std::pair<std::string, std::string> Option;
   typedef std::list<Option> Options;
   typedef std::list<std::string> Args;

   Options options;
   Args args;

   void parse(int argc, char** argv, const char* optstr);
};

TESTCPP_NS_END

#endif


#ifndef __TESTCPP_NAME_MATCHER_H
#define __TESTCPP_NAME_MATCHER_H

#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

////////////////////////////////////////////////////
struct NameMatcher
{
   virtual bool matches(const std::string& name) const = 0;

   virtual ~NameMatcher() {}
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif


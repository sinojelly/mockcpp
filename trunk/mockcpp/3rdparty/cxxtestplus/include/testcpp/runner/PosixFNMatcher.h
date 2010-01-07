#ifndef __TESTCPP_POSIX_FN_MATCHER_H
#define __TESTCPP_POSIX_FN_MATCHER_H

#include <testcpp/testcpp.h>

#include <testcpp/runner/NameMatcher.h>

TESTCPP_NS_START

////////////////////////////////////////////////////
struct PosixFNMatcher
   : public NameMatcher
{
   PosixFNMatcher(const std::string& namePattern);

   bool matches(const std::string& name) const;

private:

   std::string pattern;
};

////////////////////////////////////////////////////

TESTCPP_NS_END

#endif


#ifndef __TESTNGPPST_POSIX_FN_MATCHER_H
#define __TESTNGPPST_POSIX_FN_MATCHER_H

#include <testngppst/testngppst.h>

#include <testngppst/runner/NameMatcher.h>

TESTNGPPST_NS_START

////////////////////////////////////////////////////
struct PosixFNMatcher
   : public NameMatcher
{
   PosixFNMatcher(const std::string& namePattern);

   bool matches(const std::string& name) const;

   std::string getPattern() const;
private:

   std::string pattern;
};

////////////////////////////////////////////////////

TESTNGPPST_NS_END

#endif


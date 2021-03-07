

#include <iostream>

#if defined(_MSC_VER) || defined(__MINGW32__)
#include "Win32Fnmatch.h"
#else
#include <fnmatch.h>
#endif

#include <testngpp/runner/PosixFNMatcher.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
PosixFNMatcher::
PosixFNMatcher(const std::string& namePattern)
   : pattern(namePattern)
{
}

////////////////////////////////////////////////////
namespace
{
   const int flags = FNM_CASEFOLD|FNM_NOESCAPE; 
}

////////////////////////////////////////////////////
bool PosixFNMatcher::
matches(const std::string& name) const
{
  if(name.size() == 0)
  {
     return false;
  }

  return ::fnmatch(pattern.c_str(), name.c_str(), flags) == 0;
}

////////////////////////////////////////////////////////
std::string
PosixFNMatcher::
getPattern() const
{
   return pattern;
}

TESTNGPP_NS_END

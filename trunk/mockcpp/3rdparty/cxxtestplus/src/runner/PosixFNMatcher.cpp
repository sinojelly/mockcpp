
#include <fnmatch.h>

#include <testcpp/runner/PosixFNMatcher.h>

TESTCPP_NS_START

////////////////////////////////////////////////////////
PosixFNMatcher::
PosixFNMatcher(const std::string& namePattern)
   : pattern(namePattern)
{
}

////////////////////////////////////////////////////
namespace
{
   const int flags = FNM_CASEFOLD; 
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

TESTCPP_NS_END

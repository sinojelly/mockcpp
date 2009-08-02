
#ifndef __CPP_CHECKER_H
#define __CPP_CHECKER_H

#include <string>

namespace cpp
{
  struct Checker
  {
      virtual bool check(const std::string& user) const = 0;
      virtual ~Checker() {}
  };
}

#endif


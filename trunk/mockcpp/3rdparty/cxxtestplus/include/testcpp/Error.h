
#ifndef __TEST_CPP_ERROR_H
#define __TEST_CPP_ERROR_H

#include <exception>
#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct Error : public std::exception
{
   Error(const std::string& msg)
		: reason(msg)
   {}
   ~Error() throw() {}

   const char* what() const throw()
   {
      return reason.c_str();
   }

private:
   std::string reason;
};

TESTCPP_NS_END

#endif

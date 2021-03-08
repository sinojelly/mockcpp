/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef __TESTNGPPST_ERROR_H
#define __TESTNGPPST_ERROR_H

#include <exception>
#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct Error : public std::exception
{
   Error(const std::string& msg)
		: reason(msg)
   {}
   ~Error() TESTNGPPST_THROW() {}

   const char* what() const TESTNGPPST_THROW()
   {
      return reason.c_str();
   }

private:
   std::string reason;
};

TESTNGPPST_NS_END

#endif


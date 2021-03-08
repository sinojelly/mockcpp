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

#ifndef __TESTNGPPST_EXCEPTION_H_
#define __TESTNGPPST_EXCEPTION_H_

#include <string>
#include <exception>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct Exception: public std::exception
{
public:
   ~Exception() TESTNGPPST_THROW()
   {}

   const std::string& getFileName() const;
   unsigned int getLineOfFile() const;
   const char* what() const TESTNGPPST_THROW();

private:
   std::string fileName;
   unsigned int lineNumber;
   std::string errMsg;

protected:
   Exception( const std::string& file
            , unsigned int line
            , const std::string& msg);

};

TESTNGPPST_NS_END

#endif

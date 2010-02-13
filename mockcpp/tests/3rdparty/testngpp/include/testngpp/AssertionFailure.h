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

#ifndef __TESTNGPP_ASSERTION_FAILURE_H
#define __TESTNGPP_ASSERTION_FAILURE_H

#include <string>
#include <exception>

#include <testngpp/testngpp.h>

TESTNGPP_NS_START

struct AssertionFailure : public std::exception
{
	AssertionFailure( const std::string& file
                   , unsigned int line
                   , const std::string& msg);
	~AssertionFailure() TESTNGPP_THROW()
   {}

	const std::string& getFileName() const;
   unsigned int getLineOfFile() const;
	const char* what() const TESTNGPP_THROW();

private:
	std::string fileName;
   unsigned int lineNumber;
   std::string errMsg;
};

bool operator==( const AssertionFailure& lhs
               , const AssertionFailure& rhs);

TESTNGPP_NS_END

#endif


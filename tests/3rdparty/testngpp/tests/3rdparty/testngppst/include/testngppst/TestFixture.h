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

#ifndef __TESTNGPPST_FIXTURE_H
#define __TESTNGPPST_FIXTURE_H

#include <string>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCaseInfoReader;
struct TestCaseResultCollector;
struct MemChecker;

struct TestFixture
{
   TestFixture() : testcase(0), collector(0), memLeakCollector(0) {}

	virtual void setUp() {}
	virtual void tearDown() {}

   virtual ~TestFixture() {}

   //////////////////////////////////////////////
   void reportInfo(const char* file, unsigned int line, const std::string& info);
   void reportWarning(const char* file, unsigned int line, const std::string& warning);
   void reportFailure(const char* file, unsigned int line, const std::string& failure, bool throwException=true);

   //////////////////////////////////////////////
   void reportMemLeakInfo(const char* file, unsigned int line, const std::string& info);
   void reportMemLeakFailure(const char* file, unsigned int line, const std::string& failure, bool throwException=true);

   //////////////////////////////////////////////
   void setCurrentTestCase(const TestCaseInfoReader*, TestCaseResultCollector*, TestCaseResultCollector*, MemChecker*);

   //////////////////////////////////////////////
   void startMemChecker();
   void verifyMemChecker();

private:

   const TestCaseInfoReader* testcase;
   TestCaseResultCollector* collector;
   TestCaseResultCollector* memLeakCollector; 
   MemChecker* memChecker;
};

TESTNGPPST_NS_END

#endif


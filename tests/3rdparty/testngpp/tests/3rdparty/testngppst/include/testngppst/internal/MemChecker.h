/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2011>  <Chen Guodong: sinojelly@gmail.com>

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

#ifndef __TESTNGPPST_MEM_CHECKER_H
#define __TESTNGPPST_MEM_CHECKER_H

#include <testngppst/testngppst.h>


TESTNGPPST_NS_START

struct TestCase;

struct MemChecker
{
    MemChecker(TestCase *testcase);
	
    void start();
	void verify();
	
	static void setGlobalOpen(bool globalOpen);

private:
	bool isOpenInAnnotation();
	bool needMemCheck();
	
private:
    static bool isGlobalOpen;
	bool isTestOpen;
	TestCase *testcase;
};


TESTNGPPST_NS_END

#endif


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

#ifndef __TESTNGPPST_TEST_DEF_MACROS_H
#define __TESTNGPPST_TEST_DEF_MACROS_H

#include <testngppst/testngppst.h>
#include <testngppst/TestModule.h>

#define __TESTNGPPST_LINENAME_CAT( name, line ) name##line
#define __LINENAME( name, line ) __TESTNGPPST_LINENAME_CAT( name, line )
#define __TESTNGPPST_LINENAME( name ) __LINENAME( name, __LINE__ )

#define TEST(name, ...)            void __TESTNGPPST_LINENAME(test_) (void)
#define PTEST(paralist, name, ...) void __TESTNGPPST_LINENAME(test_) paralist
#define FIXTURE(cut, ...) struct Test##cut: public TESTNGPPST_NS::TestFixture

#define SETUP() void setUp()
#define TEARDOWN() void tearDown()

#define MODULE(module, type, ...) struct Module##module : public TESTNGPPST_NS::TestModule<type>
#define IMPORT(module, instance, tests) Module##module module##instance

#endif


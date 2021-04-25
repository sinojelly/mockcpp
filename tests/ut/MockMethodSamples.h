/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Chen Guodong : sinojelly@163.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/
#include <testngpp/testngpp.hpp>
#include <mockcpp/mokc.h>
#include <mockcpp/mockcpp.hpp>

#include <memory>

USING_TESTNGPP_NS
USING_MOCKCPP_NS


class Base1 {
public:
    virtual int method1(int a) {
    }
    virtual float method2(float a) {
    }
    virtual ~Base1(){}
};

class Base2 {
public:
    virtual int method3(int a) {
    }
    virtual float method4(float a) {
    }
    virtual ~Base2(){}
};

class Derived : public Base1, public Base2 {
public:
    virtual int method5(int a) {
    }
    virtual float method6(float a) {
    }
    virtual ~Derived(){}
};

FIXTURE(MockMethodSamples) 
{
    TEST(Can mock method in second Base class)
    {
        MockObject<Derived> mocker;
        MOCK_METHOD(mocker, method3)
            .expects(once())
            .with(eq(10))
            .will(returnValue(11));
        ASSERT_EQ(11, mocker->method3(10));
        mocker.verify();
    }

};
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

class Obj {
public:
    int val;

    bool operator==(const Obj& other) {
        return val == other.val;
    }
};

struct Interface {
    virtual void func1(std::unique_ptr<int> a) {
        std::cout << "when call func : " << a.get() << std::endl;
    }
    virtual void func2(Obj b) {
        std::cout << "when call func : " << b.val << std::endl;
    }
    virtual void func3(std::shared_ptr<int> c) {
        std::cout << "when call func : " << c.get() << std::endl;
    }
    virtual ~Interface(){}
};


FIXTURE(TestSmartPointerChecker) 
{
    TEST(Can check normal Obj)
    {
        Obj b;
        b.val = 100;
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func2)
            .expects(once())
            .with(eq(b));
        mocker->func2(b);
        mocker.verify();
    }

    TEST(Can check unique_ptr parameter) 
    {
        std::unique_ptr<int> intPtr = std::make_unique<int>(10);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func1)
            .expects(once())
            .with(eq<int, std::default_delete<int>>(intPtr.get()));
        mocker->func1(std::move(intPtr));
        mocker.verify();
    }

    TEST(Can check shared_ptr parameter, shared_ptr just looks like a normal object)
    {
        std::shared_ptr<int> intPtr = std::make_shared<int>(20);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func3)
            .expects(once())
            .with(eq(intPtr));
        mocker->func3(intPtr);
        mocker.verify();
    }

};
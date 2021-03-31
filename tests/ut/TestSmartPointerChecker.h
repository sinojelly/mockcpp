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
        //return val == other.val;
        return this == &other;
    }
};

struct Interface {
    virtual void func1(std::unique_ptr<int> a) {
        std::cout << "when call func : " << a.get() << std::endl;
    }
    virtual void func2(Obj b) {
        std::cout << "when call func : " << b.val << std::endl;
    }
    virtual ~Interface(){}
};


FIXTURE(TestSmartPointerChecker) 
{
#if 0
    TEST(Test check normal Obj)
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
#endif
    TEST(Can check unique_ptr parameter) 
    {
        std::unique_ptr<int> intPtr = std::make_unique<int>(10);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func1)
            .expects(once())
            .with(eq<int, std::default_delete<int>>(intPtr.get()));
        int* origin = intPtr.get();
        std::cout << "in eq : " << origin << std::endl;
        std::cout << "unique_ptr addr : " << &intPtr << std::endl;
        //(new Interface())->func1(std::move(intPtr));
        mocker->func1(std::move(intPtr));
        mocker.verify();
    }

};
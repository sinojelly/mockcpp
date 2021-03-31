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
    Obj(int v) : val(v) {}

    int val;

    bool operator==(const Obj& other) {
        return val == other.val;
    }
};

struct Interface {
    virtual void func1(Obj b) {
    }
    virtual void func2(std::unique_ptr<int> a) {
    }
    virtual void func3(std::shared_ptr<int> c) {
    }
    virtual void func4(std::unique_ptr<Obj> a) {
    }
    virtual void func5(std::shared_ptr<Obj> c) {
    }
    virtual ~Interface(){}
};


FIXTURE(TestSmartPointerChecker) 
{
    TEST(Can check normal Obj)
    {
        Obj b(100);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func1)
            .expects(once())
            .with(eq(b));
        mocker->func1(b);
        mocker.verify();
    }

    TEST(Can check unique_ptr<int> parameter) 
    {
        auto intPtr = std::make_unique<int>(10);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func2)
            .expects(once())
            .with(eq<int>(intPtr.get())); // Must use eq<int> or eq<int, std::default_delete<int>>
        mocker->func2(std::move(intPtr));
        mocker.verify();
    }

    TEST(Can check shared_ptr<int> parameter, shared_ptr just looks like a normal object)
    {
        auto intPtr = std::make_shared<int>(20);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func3)
            .expects(once())
            .with(eq(intPtr));
        mocker->func3(intPtr);
        mocker.verify();
    }

    TEST(Can check unique_ptr<Obj> parameter)
    {
        auto ptr = std::make_unique<Obj>(200);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func4)
            .expects(once())
            .with(eq<Obj>(ptr.get())); // Must use eq<Obj> or eq<Obj, std::default_delete<Obj>>
        mocker->func4(std::move(ptr));
        mocker.verify();
    }

    TEST(Can check shared_ptr<Obj> parameter, shared_ptr just looks like a normal object)
    {
        auto ptr = std::make_shared<Obj>(300);
        MockObject<Interface> mocker;
        MOCK_METHOD(mocker, func5)
            .expects(once())
            .with(eq(ptr));
        mocker->func5(ptr);
        mocker.verify();
    }

};
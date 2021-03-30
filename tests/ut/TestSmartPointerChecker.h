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

struct Interface {
    virtual void func1(std::unique_ptr<int> a) = 0;
    virtual ~Interface(){}
};

FIXTURE(TestSmartPointerChecker) 
{

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
};
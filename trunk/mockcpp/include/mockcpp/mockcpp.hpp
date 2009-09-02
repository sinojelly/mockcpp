/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

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

#ifndef __MOCKCPP_HPP_
#define __MOCKCPP_HPP_

#include <mockcpp/mockcpp.h>
#include <mockcpp/MockObject.h>
#include <mockcpp/ChainingMockHelper.h>

#define METHOD(m) method(&m, #m)

#  include <boost/typeof/typeof.hpp>
#define MOCK_METHOD(obj, m) \
   typedef BOOST_TYPEOF(obj) mockcpp_ ##obj## _MockObjectType; \
   typedef mockcpp_ ##obj## _MockObjectType::MockedInterface mockcpp_ ##obj## _MockedInterface; \
   obj.method(&mockcpp_ ##obj## _MockedInterface::m, \
        (MOCKCPP_NS::TypeString<mockcpp_ ##obj## _MockedInterface>::value() + "::"#m).c_str())

#endif


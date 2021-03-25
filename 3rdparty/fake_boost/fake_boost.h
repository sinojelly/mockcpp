/***
   mockcpp is a C/C++ mock framework.
   Copyright [2021] [Chen Guodong <sinojelly@163.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#ifndef __FAKE_BOOST__
#define __FAKE_BOOST__

/*
*  This file is used to be compatible with most compilers that support c++ 11 without boost (it's too big).
*  If you use an old compiler or meet some problem, you can try the real boost.
*/
// not support c++ 11
#if __cplusplus <= 199711L && \
    (!defined(_MSC_VER) || _MSC_VER < 1600) && \
    (!defined(__GNUC__) || \
      (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ < 40603))

template <bool condition>
struct static_assert
{
    typedef int static_assert_failure[condition ? 1 : -1];
};

#if NO_BOOST
#error "You need boost to make it work, please download boost at url(https://gitee.com/sinojelly/boost) and put it in mockcpp/3rdparty"
#else
#include <boost/type_traits/is_enum.hpp>
#define FAKE_BOOST_IS_ENUM boost::is_enum
#include <boost/typeof/typeof.hpp>
#define FAKE_BOOST_TYPEOF BOOST_TYPEOF
#endif // NO_BOOST

#else
// support c++ 11

// support static_assert, std::is_enum
#define FAKE_BOOST_IS_ENUM std::is_enum

// support decltype, but not support typeof on MSVC.
#if defined(__GNUC__)
#include <type_traits>
#define FAKE_BOOST_TYPEOF __typeof
#else

//The decltype type specifier is supported in Visual Studio 2010 or later versions
#define __DECLTYPE_TO_TYPEOF(x) std::decay<decltype((x))>::type
#define FAKE_BOOST_TYPEOF __DECLTYPE_TO_TYPEOF

#endif // __GNUC__

#endif // not support cplusplus 11


#endif // __FAKE_BOOST__

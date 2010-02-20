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

#ifndef __TESTNGPP_ASSERTER_H
#define __TESTNGPP_ASSERTER_H

#include <sstream>
#include <string.h>

#include <testngpp/testngpp.h>
#include <testngpp/utils/Formatter.h>


#if defined(__GNUC__)
#define TESTNGPP_TYPEOF(expr) typeof(expr)
#else
#include <boost/typeof/typeof.hpp>
#define TESTNGPP_TYPEOF(expr) BOOST_TYPEOF(expr)
#endif

TESTNGPP_NS_START

//////////////////////////////////////////////////////////////////
#define __TESTNGPP_REPORT_FAILURE(what) \
      reportFailure(__FILE__, __LINE__, what)

//////////////////////////////////////////////////////////////////
#define ASSERT_TRUE(expr) do { \
   if(!(expr)) {\
      __TESTNGPP_REPORT_FAILURE("expected (" #expr ") being TRUE, but it's actually FALSE"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_FALSE(expr) do { \
   if(expr) {\
      __TESTNGPP_REPORT_FAILURE("expected (" #expr ") being FALSE, but it's actually TRUE"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __TESTNGPP_MAKE_STR(expr) " " #expr " "

//////////////////////////////////////////////////////////////////
#define __TESTNGPP_ASSERT_EQUALITY(expected, expected_equality, wrong_equality, value) do {\
   TESTNGPP_TYPEOF(expected) __testngpp_expected = (expected); \
   TESTNGPP_TYPEOF(value) __testngpp_value = (value); \
   if(__testngpp_expected wrong_equality __testngpp_value) { \
      std::stringstream ss; \
      ss << "expected (" #expected __TESTNGPP_MAKE_STR(expected_equality) #value "), found (" \
         << TESTNGPP_NS::toTypeAndValueString(__testngpp_expected) \
         << __TESTNGPP_MAKE_STR(wrong_equality) \
         << TESTNGPP_NS::toTypeAndValueString(__testngpp_value) \
         << ")"; \
      __TESTNGPP_REPORT_FAILURE(ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_EQ(expected, value) \
   __TESTNGPP_ASSERT_EQUALITY(expected, ==, !=, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_NE(expected, value) \
   __TESTNGPP_ASSERT_EQUALITY(expected, !=, ==, value)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS(expr, except) do { \
   bool testngpp_caught_exception = false; \
   try { \
      expr; \
   }catch(except&){ \
      testngpp_caught_exception = true; \
   } catch(...) {\
	  __TESTNGPP_REPORT_FAILURE( \
         "expected " #expr " will throw an exception of type " #except ", but actually raised a different kind of exception."); \
   } \
   if(!testngpp_caught_exception) { \
      __TESTNGPP_REPORT_FAILURE( \
         "expected " #expr " will throw an exception of type " #except ", but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS_ANYTHING(expr) do { \
   bool __testngpp_caught_exception = false; \
   try { \
      expr; \
   }catch(...){ \
      __testngpp_caught_exception = true; \
   } \
   if(!__testngpp_caught_exception) { \
      __TESTNGPP_REPORT_FAILURE ( \
         "expected " #expr " will throw an exception of any type, but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS_NOTHING(expr) do { \
   try { \
      expr; \
   }catch(...){ \
      __TESTNGPP_REPORT_FAILURE ( \
          "expected " #expr " will not throw any exceptions, but it actually did."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_THROWS_EQUALS(expr, except, expected, value) do { \
   try { \
      expr; \
      __TESTNGPP_REPORT_FAILURE ( \
          "expected " #expr " will throw an exception of type " #except ", but actually not."); \
   }catch(except){ \
      ASSERT_EQ(expected, value); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define ASSERT_SAME_DATA(addr1, addr2, size) do { \
   void* p1 = reinterpret_cast<void*>(addr1); \
   void* p2 = reinterpret_cast<void*>(addr2); \
   if(::memcmp((void*)p1, (void*)p2, size)) \
   { \
      std::stringstream ss; \
      ss << "expected (" #addr1 ", " #addr2 ") have same data, found (" \
         << TESTNGPP_NS::toBufferString(p1, size) \
         << ", " \
         << TESTNGPP_NS::toBufferString(p2, size) \
         << ")"; \
      __TESTNGPP_REPORT_FAILURE(ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define __TESTNGPP_ABS(value) ((value) > 0?(value):-(value))
//////////////////////////////////////////////////////////////////
#define ASSERT_DELTA(x, y, d) do { \
   TESTNGPP_TYPEOF(x) value1 = x; \
   TESTNGPP_TYPEOF(y) value2 = y; \
   TESTNGPP_TYPEOF(d) delta  = __TESTNGPP_ABS(d); \
   TESTNGPP_TYPEOF(d) actual_delta = __TESTNGPP_ABS(value1 - value2); \
   if(actual_delta > delta) \
   { \
      std::stringstream ss; \
      ss << "expected the delta of (" #x ", " #y ") <= (" \
         << TESTNGPP_NS::toTypeAndValueString(delta) \
         << "), actual delta: (" \
         << TESTNGPP_NS::toTypeAndValueString(actual_delta) \
         << ")"; \
      __TESTNGPP_REPORT_FAILURE(ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define FAIL(msg) do { \
    __TESTNGPP_REPORT_FAILURE(msg); \
}while(0)

//////////////////////////////////////////////////////////////////
#define WARN(msg) do { \
    reportWarning(__FILE__, __LINE__, msg); \
}while(0)

//////////////////////////////////////////////////////////////////
#define INFO(msg) do { \
    reportInfo(__FILE__, __LINE__, msg); \
}while(0)

//////////////////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif


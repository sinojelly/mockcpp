
#ifndef __TESTCPP_ASSERTER_H
#define __TESTCPP_ASSERTER_H

#include <testcpp/testcpp.h>
#include <testcpp/AssertionFailure.h>
#include <testcpp/utils/Formatter.h>
#include <sstream>

TESTCPP_NS_START

//////////////////////////////////////////////////////////////////
#define TS_ASSERT(expr) do { \
   if(!(expr)) {\
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
         "expected (" #expr ") being TRUE, but it's actually FALSE"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_TRUE(expr) TS_ASSERT(expr)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_FALSE(expr) do { \
   if(expr) {\
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
         "expected (" #expr ") being FALSE, but it's actually TRUE"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_EQUALS(expected, value) do { \
   typeof(expected) __expected = (expected); \
   typeof(value) __value = (value); \
   if(__expected != __value) { \
      std::stringstream ss; \
      ss << "expected (" #expected " == " #value "), but actually got (" \
         << TESTCPP_NS::toTypeAndValueString(__expected) \
         << " != " \
         << TESTCPP_NS::toTypeAndValueString(__value) \
         << ")"; \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_NOT_EQUALS(expected, value) do { \
   typeof(expected) __expected = (expected); \
   typeof(value) __value = (value); \
   if(__expected == __value) {\
      std::stringstream ss; \
      ss << "expected (" #expected " != " #value "), but actually got (" \
         << TESTCPP_NS::toTypeAndValueString(__expected) \
         << " == " \
         << TESTCPP_NS::toTypeAndValueString(__value) \
         << ")"; \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_THROWS(expr, except) do { \
   bool testcpp_caught_exception = false; \
   try { \
      expr; \
   }catch(except&){ \
      testcpp_caught_exception = true; \
   } \
   if(!testcpp_caught_exception) { \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
         "expected " #expr " will throw an exception of type " #except ", but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_THROWS_ANYTHING(expr) do { \
   bool testcpp_caught_exception = false; \
   try { \
      expr; \
   }catch(...){ \
      testcpp_caught_exception = true; \
   } \
   if(!testcpp_caught_exception) { \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
         "expected " #expr " will throw an exception of any type, but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_THROWS_NOTHING(expr) do { \
   try { \
      expr; \
   }catch(...){ \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
          "expected " #expr " will not throw any exceptions, but it actually did."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_THROWS_EQUALS(expr, except, expected, value) do { \
   try { \
      expr; \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
          "expected " #expr " will throw an exception of type " #except ", but actually not."); \
   }catch(except){ \
      TS_ASSERT_EQUALS(expected, value); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_FAIL(msg) do { \
    throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, msg); \
}while(0)

//////////////////////////////////////////////////////////////////

TESTCPP_NS_END

#endif


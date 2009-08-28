
#ifndef __TESTCPP_ASSERTER_H
#define __TESTCPP_ASSERTER_H

#include <testcpp/testcpp.h>
#include <testcpp/AssertionFailure.h>
#include <testcpp/Formatter.h>
#include <sstream>

TESTCPP_NS_START

//////////////////////////////////////////////////////////////////
#define TS_ASSERT(expr) do { \
   if(!(expr)) {\
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, "expected (" #expr "), but turns out it's not true"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_FALSE(expr) do { \
   if(expr) {\
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, "expected (" #expr ") being false, but turns out it's true"); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_EQUALS(expected, value) do { \
   if(expected != value) { \
      std::stringstream ss; \
      ss << "expected (" #expected " == " #value "), but actually got (" \
         << TESTCPP_NS::toTypeAndValueString(expected) \
         << " != " \
         << TESTCPP_NS::toTypeAndValueString(value) \
         << ")"; \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, ss.str()); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_NOT_EQUALS(expected, value) do { \
   if(expected == value) {\
      std::stringstream ss; \
      ss << "expected (" #expected " != " #value "), but actually got (" \
         << TESTCPP_NS::toTypeAndValueString(expected) \
         << " == " \
         << TESTCPP_NS::toTypeAndValueString(value) \
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
         "expected " #expr " will throw exception of any type, but actually not."); \
   } \
}while(0)

//////////////////////////////////////////////////////////////////
#define TS_ASSERT_THROWS_NOTHING(expr) do { \
   try { \
      expr; \
   }catch(...){ \
      throw TESTCPP_NS::AssertionFailure(__FILE__, __LINE__, \
          "expected " #expr " will not throw exceptions, but it actually did."); \
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


#ifndef __TESTNGPP_MY_TEST_CASE_H__
#define __TESTNGPP_MY_TEST_CASE_H__

#include <testngpp/internal/TestCase.h>
#include <testngpp/TestFixture.h>

struct MyTestCase : public TESTNGPP_NS::TestCase
{
   MyTestCase( const std::string& nameOfCase
           , const std::string& nameOfFixture
           , TESTNGPP_NS::TestCase* depends
           , const std::string& file
           , unsigned int line)
           : TESTNGPP_NS::TestCase(nameOfCase, nameOfFixture, "MySuite", depends, file, line)
   {}

   MyTestCase( const std::string& nameOfCase
           , const std::string& nameOfFixture
           , const std::string& file
           , unsigned int line)
           : TESTNGPP_NS::TestCase(nameOfCase, nameOfFixture, "MySuite", 0, file, line)
   {}

   TESTNGPP_NS::TestFixture* getFixture() const { return 0; }
   void setFixture(TESTNGPP_NS::TestFixture* fixture) { }
   void runTest() {}
};

#endif


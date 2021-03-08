
#include <iostream>
#include <cxxtest/TestSuite.h>
#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/utils/StringToOptions.h>

USING_TESTNGPP_NS

class TestStringToOptions: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();
   }
   void tearDown()
   {
      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleString()
   {
     TS_ASSERT_EQUALS(3, StringToOptions::getNumberOfArgsInString("abc bc c"));
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleStringWithLeadingBlank()
   {
     TS_ASSERT_EQUALS(3, StringToOptions::getNumberOfArgsInString(" a bcd c"));
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleStringWithTrailingBlank()
   {
     TS_ASSERT_EQUALS(3, StringToOptions::getNumberOfArgsInString("abc bcd cdef "));
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleStringWithLeadingAndTrailingBlank()
   {
     TS_ASSERT_EQUALS(3, StringToOptions::getNumberOfArgsInString(" abc bcd c "));
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleStringWithTab()
   {
     TS_ASSERT_EQUALS(3, StringToOptions::getNumberOfArgsInString("	 abc		bcd c	 	"));
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleStringWithDoubleQuoteOptions()
   {
     TS_ASSERT_EQUALS(2, StringToOptions::getNumberOfArgsInString("abc \"bcd cdef\" "));
   }

   void testShouldBeAbleToGetNumberOfArgsOfSimpleStringWithDoubleQuoteInsideOptions()
   {
     TS_ASSERT_EQUALS(3, StringToOptions::getNumberOfArgsInString(" ./abc -l\" bcd -lcdef -s \" -s "));
   }

   void testShouldBeAbleToParseToCArgs()
   {
      StringToOptions::CArgs cargs = StringToOptions::parse(" ./abc -l\" bcd -lcdef -s \" -s");

      TS_ASSERT_EQUALS(3, cargs.first);

      TS_ASSERT(0 != cargs.second[0]);
      TS_ASSERT(0 != cargs.second[1]);
      TS_ASSERT(0 != cargs.second[2]);

      TS_ASSERT_EQUALS(std::string("./abc"), std::string(cargs.second[0]));
      TS_ASSERT_EQUALS(std::string("-l\" bcd -lcdef -s \""), std::string(cargs.second[1]));
      TS_ASSERT_EQUALS(std::string("-s"), std::string(cargs.second[2]));

      delete [] cargs.second[0];
      delete [] cargs.second[1];
      delete [] cargs.second[2];
      delete [] cargs.second;
   }
};


#include <cxxtest/TestSuite.h>

#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/runner/PosixFNMatcher.h>

USING_TESTNGPP_NS

class TestPosixFNMatcher: public CxxTest::TestSuite
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

   void testShouldBeAbleToUseWildCard()
   {
      PosixFNMatcher matcher("*");

      TS_ASSERT(matcher.matches("abc"));
      TS_ASSERT(matcher.matches("123"));
   }

   void testShouldNotMatchEmptyStringEvenThePatternIsWildcard()
   {
      PosixFNMatcher matcher("*");

      TS_ASSERT(!matcher.matches(""));
   }

   void testShouldBeAbleToUsePartialWildcard()
   {
      PosixFNMatcher matcher("abc*efg");

      TS_ASSERT(matcher.matches("abcd123efg"));
      TS_ASSERT(!matcher.matches("abcd123fg"));
      TS_ASSERT(!matcher.matches("abd123efg"));
   }

   void testShouldBeAbleToUseSingleCharPattern()
   {
      PosixFNMatcher matcher("abc?e??fg");

      TS_ASSERT(matcher.matches("abc0e12fg"));
      TS_ASSERT(!matcher.matches("abcde123fg"));
      TS_ASSERT(!matcher.matches("abcffedg"));
   }

   void testShouldIgnoreCaseRestriction()
   {
      PosixFNMatcher matcher("abc?e??fg");

      TS_ASSERT(matcher.matches("aBc0E12fg"));
      TS_ASSERT(matcher.matches("ABc0E12fG"));
   }

};

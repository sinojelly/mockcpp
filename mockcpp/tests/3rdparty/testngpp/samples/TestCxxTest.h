
#include <cstdlib>
#include <string>

#include <cxxtest/TestSuite.h>


class TestCxxTest : public CxxTest::TestSuite
{
public:
    void setUp()
    {}

    void tearDown()
    {}

    // Success

    /* this ml-comments is for test
 as well */ // same here

    /* this msl-comments is only for test */ //it should not hurt

    // @test
    void case0()
    {
       TS_ASSERT(false);
    }
			
    // @test
    // @timeout=15s
    void case1()
    {
       TS_ASSERT(true);
    }

    // Success
    void testCase3() {}

    void testCase4()
    {
      TS_ASSERT_EQUALS(2, 2);
    }

    void testCase5()
    {
      TS_ASSERT(std::string("abc") == std::string("abc"));
    }

    // Fail
    void testCase6()
    {
      TS_FAIL("not <implemented/> <yet>.");
    }

    // Success
    void testCase7()
    {
      TS_ASSERT_THROWS_NOTHING(testCase3());
    }

    // Success
    void testCase8()
    {
      TS_ASSERT_THROWS_ANYTHING(testCase6());
    }

    void testCase9()
    {
    }

    void testCase10()
    {
    }

    void testCase11()
    {
    }

#if 0
    void testCase12()
    {
      TS_ASSERT_THROWS(testCase3(), std::exception);
    }
#endif

    void testCase13()
    {
    }

    void testCase14()
    {
    }
};


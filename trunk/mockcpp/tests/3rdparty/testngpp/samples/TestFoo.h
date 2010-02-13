
//#include <unistd.h>
#include <cstdlib>
#include <string>
#include <iostream>

#include <testngpp/testngpp.hpp>

USING_TESTNGPP_NS

struct TestFixture12 {};

class TestFoo : public TestFixture
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
       __TESTNGPP_DO

       TS_ASSERT(false);

       __TESTNGPP_CLEANUP

       TS_ASSERT(true);

       __TESTNGPP_DONE
    }
			
    // @test
    // @timeout=15s
    void case1()
    {
       __TESTNGPP_DO

       TS_ASSERT(true);

       __TESTNGPP_CLEANUP

       TS_ASSERT(false);

       __TESTNGPP_DONE
    }

#if !defined(TESTNGPP_DISABLE_SANDBOX) || !TESTNGPP_DISABLE_SANDBOX
    // Fail
    // @test
    void case2()
    {
       ::exit(1);
    }
#endif

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

    // Fail
    void testCase9()
    {
      TS_ASSERT_THROWS_ANYTHING(testCase3());
    }

    void testCase10()
    {
      TS_ASSERT_THROWS_ANYTHING(testCase6());
    }

    void testCase11()
    {
      TS_ASSERT_THROWS_NOTHING(testCase3());
    }

#if 0
    void testCase12()
    {
      TS_ASSERT_THROWS(testCase3(), std::exception);
    }
#endif

    void testCase13()
    {
      TS_ASSERT_THROWS(testCase3(), std::exception);
    }

    void testCase14()
    {
      TS_ASSERT_THROWS(testCase3(), std::exception);
    }
};


FIXTURE(ChineseFixture, 中文套件样例)
{
    void func()
    {
       throw 1;
    }

    TEST(测试用例1)
    {
      TS_ASSERT_THROWS_NOTHING(func());
    }

    TEST(测试用例2)
    {
      TS_ASSERT(std::string("abc") == std::string("abcd"));
    }

    TEST(测试用例3)
    {
      int a = 1;
      int b = 1;

      TS_ASSERT_EQUALS(a, b);
    }
};

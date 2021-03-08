
#include <cstdlib>
#include <string>
#include <iostream>

#include <testngpp/testngpp.hpp>

USING_TESTNGPP_NS

struct CFoo
{
   virtual void foo() = 0;
   virtual ~CFoo() {}
};

struct Hell : public CFoo
{
   Hell() { p = new char[10]; }
   ~Hell() { delete [] p; }

   void foo() {}

   char *p;
};

Hell hell[100];

struct TestBar1 : public TESTNGPP_NS::TestFixture
{
    Hell* hellInstance;

    struct CBar : public CFoo{
        void foo() {}
        void testNothing() {}
    };

    struct CBar;
    struct CBar cbar;
    struct CBar cbars[2][5];

    SETUP()
    {
    }

    TEARDOWN()
    {
    }

    // @test(id=1, depends=4, tags="ft slow")
    void case10()
    {
       INFO("this is case 10");
       ASSERT_FALSE(true);
    }

/*
    A possible way to write annotation:


    /// @test( depends=load
    ///      , tags="it fast" )
    ///
    /// @desc("测试ASSERT_TRUE")

    void compare(unsigned int a, CFoo* foo)
    {
        ASSERT_EQ(a, foo->getValue());
    }

*/
    // @test( id=2 , depends=1 , tags="it fast")
    void case11()
    {
       INFO("this is case 11");
       ASSERT_TRUE(true);
    }

    // @test(id=3)
    TEST(case13)
    { INFO("this is case 13"); }
			
    // @test(id=4, depends=3, tags="it slow")
    TEST(case14)
    {
       INFO("this is case 14");
#if defined(__GNUC__)
       ASSERT_TRUE(true);
#endif
    }

#if defined(__GNUC__)
    // @test(depends=4, tags="ut fast")
    TEST(case15)
    {
       INFO("this is case 15");
       ASSERT_FALSE(true);
    }
#else
    // @test(depends=2, tags="ft slow empty")
    TEST(case16)
    {
       INFO("this is case 16");
	    exit(-1);
	 }
#endif
};

class TestBar2 : public TestFixture
{
public:
    // @test(id=1)
    void case20()
    {
      WARN("this test is gonna crash 'coz of invalid memory access");
	   char* p = 0;
	  // (*p) = 0;  // Note: avoid crash to run the PTEST.
      TS_ASSERT(true);
    }

};

// @fixture(tags=succ)
struct TestBar3 : public TESTNGPP_NS::TestFixture
{
   // @test
   void case30() {ASSERT_FALSE(true);}

   // @test
   void case31()
   {}

   // @test
   void case32()
   {}

   // @test
   void case33()
   {}

   // @test
   void case34()
   {}

   // @test
   void case35()
   {}

   // @test
   void case36()
   {}

   // @test
   void case37()
   {}

   // @test
   void case38()
   {}

   // @test
   void case39()
   {}
};




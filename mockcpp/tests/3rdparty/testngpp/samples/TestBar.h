
#include <cstdlib>
#include <string>
#include <iostream>

#include <testcpp/testcpp.hpp>

USING_TESTCPP_NS

struct ABC
{
   ABC() { p = new char[10]; }
   ~ABC() { delete [] p; }

   char *p;
};

ABC abc;

struct TestBar1 : public TESTCPP_NS::TestFixture
{
    // @test(id=1, depends=4, tags="ft slow")
    void case10()
    {
       TS_ASSERT(false);
    }

    // @test(id=2, depends=1, tags="it fast")
    void case11()
    {
       TS_ASSERT(true);
    }

    TEST(case13)
    {
    }
			
    // @test(id=4, tags="it slow")
    TEST(case14)
    {
	   //exit(-1);
       TS_ASSERT(true);
    }

    // @test(depends=4, tags="ut fast")
    TEST(case15)
    {
       TS_ASSERT(true);
    }

    // @test(depends=2, tags="ft slow empty")
    TEST(case16)
    {
	    exit(-1);
	}
};

class TestBar2 : public TestFixture
{
public:
    // @test
    void case20()
    {
	   char* p = 0;
	   (*p) = 0;
      TS_ASSERT(true);
    }
};

// @fixutre(tags=succ)
struct TestBar3 : public TESTCPP_NS::TestFixture
{
   // @test
   void case30()
   {}

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

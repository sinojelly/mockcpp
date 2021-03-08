
#include <string>

#include <testngpp/internal/AssertionFailure.h>
#include <testngpp/internal/Warning.h>
#include <testngpp/internal/TestFixtureDesc.h>
#include <testngpp/internal/TestCase.h>
#include <testngpp/TestFixture.h>

#include <mockcpp/Exception.h>


USING_TESTNGPP_NS
USING_MOCKCPP_NS

class MyTestFixture : public TESTNGPP_NS::TestFixture
{
public:
   void setUp()
   {
   }

   void tearDown()
   {
   }

   void testCase1()
   {
      throw TESTNGPP_NS::AssertionFailure("MyTestFixture.h", 12, "a != b");
   }

   void testCase2()
   {
      throw TESTNGPP_NS::Warning("MyTestFixture.h", 13, "Exception");
   }

   void testCase3()
   {
   }
};

static MyTestFixture myTestFixture;

struct MyTestCase : public TESTNGPP_NS::TestCase
{
   MyTestCase(const std::string name, unsigned int line)
	  : TestCase(name, "MyTestFixture", "MySuite", 0, "MyTestFixture.h", line)
   {}

   MyTestFixture myTestFixture;

   TESTNGPP_NS::TestFixture* getFixture() const { return 0; }
   void setFixture(TESTNGPP_NS::TestFixture* fixture = 0) {}
};

static struct MyTestCase1 : public MyTestCase
{
   MyTestCase1() : MyTestCase("testCase1", 5) {}

   void runTest()
   {
      myTestFixture.testCase1();
   }
}
myTestCase1;

static struct MyTestCase2 : public MyTestCase
{
   MyTestCase2() : MyTestCase("testCase1", 5) {}

   void runTest()
   {
      myTestFixture.testCase2();
   }
}
myTestCase2;

static struct MyTestCase3 : public MyTestCase
{
   MyTestCase3() : MyTestCase("testCase1", 5) {}

   void runTest()
   {
      myTestFixture.testCase3();
   }
}
myTestCase3;

static TESTNGPP_NS::TestCase* myTestCases[] = { &myTestCase1, &myTestCase2, &myTestCase3 };

static TESTNGPP_NS::TestFixtureDesc myTestFixtureDesc("MyTestFixture", "MyTestFixture.h", myTestCases, 3);


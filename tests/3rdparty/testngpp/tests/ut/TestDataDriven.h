

#include <iostream>

//#include <testngppst/testngppst.hpp>
#include <testngppst/testngppst.h>
#include <testngppst/Asserter.h>
#include <testngppst/TestFixture.h>
#include <testngppst/TestDefMacros.h>

#include <testngpp/DataDrivenDef.h>
#include <testngpp/internal/DataDriven.h>

USING_TESTNGPP_NS

struct MyTestFixture 
{
    DATA_PROVIDER(dataProvider1, 1
             , DATA_GROUP(10)
             , DATA_GROUP(15));

    int i1;

    void testcase0(int i)
    {
       i1 = i;
    }

    double d2;
    long l2;

    DATA_PROVIDER(dataProvider2, 2
             , DATA_GROUP(10.0, 12l)
             , DATA_GROUP(15.1, 23l)
             , DATA_GROUP(16.0, 23)
             , DATA_GROUP(16, 22l)
              );

    void testcase1(double d, long l)
    {
       d2 = d;
       l2 = l;
    }
};

FIXTURE(DataDriven)
{
   MyTestFixture fixture;

   TEST($> invoke a test method with 1 parameter)
   {
      DataProvider* dataProvider = &fixture.dataProvider1;

      ASSERT_THROWS_NOTHING(runParameterizedTest
            ( &fixture, &MyTestFixture::testcase0
            , dataProvider, 0));

      ASSERT_EQ(10, fixture.i1);

      ASSERT_THROWS_NOTHING(runParameterizedTest
            ( &fixture, &MyTestFixture::testcase0
            , dataProvider, 1));

      ASSERT_EQ(15, fixture.i1);
   }

   TEST($> invoke a test method with 2 parameters)
   {
      DataProvider* dataProvider = &fixture.dataProvider2;

      ASSERT_THROWS_NOTHING(runParameterizedTest
            ( &fixture, &MyTestFixture::testcase1
            , dataProvider, 0));

      ASSERT_EQ(10.0, fixture.d2);
      ASSERT_EQ(12l,  fixture.l2);

      ASSERT_THROWS_NOTHING(runParameterizedTest
            ( &fixture, &MyTestFixture::testcase1
            , dataProvider, 1));

      ASSERT_EQ(15.1, fixture.d2);
      ASSERT_EQ(23l,  fixture.l2);
   }

   TEST(should throw exception if types mismatch)
   {
      DataProvider* dataProvider = &fixture.dataProvider2;

      ASSERT_THROWS(
            runParameterizedTest
               ( &fixture, &MyTestFixture::testcase1
               , dataProvider, 2);
            , TESTNGPP_NS::Error);

      ASSERT_THROWS(runParameterizedTest
            ( &fixture, &MyTestFixture::testcase1
            , dataProvider, 3)
            , TESTNGPP_NS::Error);
   }

   TEST($> convert data group to string)
   {
      DataProvider* dataProvider = &fixture.dataProvider1;
      
	  #ifdef _MSC_VER
      ASSERT_EQ((char const *)"10,", dataProvider->toString(0));
	  ASSERT_EQ((char const *)"15,", dataProvider->toString(1));
	  #else
      ASSERT_EQ((const char*)"10", dataProvider->toString(0));	  
	  ASSERT_EQ((const char*)"15", dataProvider->toString(1));
	  #endif     

      dataProvider = &fixture.dataProvider2;

	  #ifdef _MSC_VER
	  ASSERT_EQ((char const *)"10.0,12l", dataProvider->toString(0));
      ASSERT_EQ((char const *)"15.1,23l", dataProvider->toString(1));
	  #else
      ASSERT_EQ((const char*)"10.0, 12l", dataProvider->toString(0));
      ASSERT_EQ((const char*)"15.1, 23l", dataProvider->toString(1));
	  #endif
   }
};

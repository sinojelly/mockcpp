
#include <cppunit/extensions/HelperMacros.h>

#include <ChainingMockHelper.h>
#include <MockService.h>

#include <ServiceUser.c>

using namespace mockcpp;

class TestService : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TestService );
	CPPUNIT_TEST( test_func1_should_invoke_service_printf );
	CPPUNIT_TEST( test_func1_should_invoke_service_printf_with_any_constraints );
	CPPUNIT_TEST( test_func1_should_invoke_service_printf_with_less_constraints );
	CPPUNIT_TEST( test_func2_should_invoke_service_f1 );
	CPPUNIT_TEST( test_func2_should_invoke_service_f1_with_any_constraint );
	CPPUNIT_TEST( test_func2_should_invoke_service_f1_with_less_constraint );
	CPPUNIT_TEST( test_func2_should_invoke_service_f5 );
	CPPUNIT_TEST( test_func3_should_invoke_service_f2 );
	CPPUNIT_TEST( test_func4_should_invoke_service_f0 );
	CPPUNIT_TEST( test_func4_should_invoke_service_f0_with_eq );
	CPPUNIT_TEST( test_func4_should_invoke_service_f0_with_size );
	CPPUNIT_TEST( test_func4_should_invoke_service_f0_with_mirror);
	CPPUNIT_TEST( test_func5_should_invoke_service_f6 );
	CPPUNIT_TEST( test_func5_should_invoke_service_f6_with_eq );
	CPPUNIT_TEST( test_func6_should_invoke_service_f7 );
	CPPUNIT_TEST( test_func6_should_invoke_service_f7_as_simple_char );
	CPPUNIT_TEST( test_func5_should_invoke_service_f6_with_mirror );
	CPPUNIT_TEST( test_func6_should_invoke_service_f7_with_mirror );
	CPPUNIT_TEST( test_func6_should_invoke_service_f7_with_mirror_for_char );
	CPPUNIT_TEST( test_func6_should_invoke_service_f7_with_smirror );
	CPPUNIT_TEST( test_func7_should_invoke_service_f8 );
	CPPUNIT_TEST_SUITE_END();

public:

	void setUp()
	{
      MOCKER(service_f5)
        .defaults()
        .will(returnValue((long)0));
	}

	void tearDown()
	{
      globalMockContextVerifyAndReset();
	}

	/////////////////////////////////////////////////////////

	//
	// Should be able to support various parameters of function.
	//
	// like, int service_printf(int, ...);
	//
	void test_func1_should_invoke_service_printf()
   {
		char* s = "abc";

      MOCKER(service_printf)
        .expects(once())
        .with(eq(10), eq(true), eq(2.0))
        .will(returnValue(0));

      func1(); 
   }

   //
   // For var parameters function, when trying to specify constraints
   // by using with(...), if you are not concerned other parameters 
   // except for the first several ones, you can specify them by using
   // any() constraint.
   //
	void test_func1_should_invoke_service_printf_with_any_constraints()
   {
		char* s = "abc";

      MOCKER(service_printf)
        .expects(once())
        .with(eq(10), eq(true), any())
        .will(returnValue(0));

      func1(); 
   }

   //
   // For var parameters function, when trying to specify constraints
   // by using with(...), if you are not concerned other parameters 
   // except for the first several ones, you don't have to specify 
   // the constraints by using any(), just left it blank.
   //
	void test_func1_should_invoke_service_printf_with_less_constraints()
   {
		char* s = "abc";

      MOCKER(service_printf)
        .expects(once())
        .with(eq(10), eq(true) /*, any() */)
        .will(returnValue(0));

      func1(); 
   }

	//
	// a function without return value (void) 
	// should be supported, and you don't need to
	// specify a return value by will.
	//
	// Actually, you can still specify a return
	// value, it will be ignored anyway.
	//
   void test_func2_should_invoke_service_f1()
   {
      int i = 20;

      MOCKER(service_f1)
        .expects(once())
        .with(eq(10), eq<const int*>(&i));
        //.will(returnValue(0));

      func2(&i);
   }

   //
   // For normal functions, when trying to specify constraints
   // by using with(...), if you are not concerned other parameters 
   // except for the first several ones, you can specify them by
   // using any() constraint.
   //
   void test_func2_should_invoke_service_f1_with_any_constraint()
   {
      int i = 20;

      MOCKER(service_f1)
        .expects(once())
        .with(eq(10), any());

      func2(&i);
   }

   //
   // For normal functions, when trying to specify constraints
   // by using with(...), if you are not concerned other parameters 
   // except for the first several ones, you don't have to specify 
   // the constraints by using any(), just left it blank.
   //
   void test_func2_should_invoke_service_f1_with_less_constraint()
   {
      int i = 20;

      MOCKER(service_f1)
        .expects(once())
        .with(eq(10) /* , any() */);

      func2(&i);
   }

	//
	// Since the default return value of service_f1
	// was specified in setUp(), here, you don't have
	// to specify it if you want to use same one.
	//
   void test_func2_should_invoke_service_f5()
   {
      int i = 10;

      MOCKER(service_f1)
        .expects(once());
     
      MOCKER(service_f5)
        .expects(once())
        .with(eq(i))
        .will(returnValue((long)2));

      CPPUNIT_ASSERT_EQUAL((long)2, func2(&i));
   }

   //
   // A pointer could be outbounded by outBoundP()
   //
   void test_func3_should_invoke_service_f2()
   {
      st_struct_1* st1 = new st_struct_1;
      st1->field0 = 100;

      MOCKER(service_f2)
        .expects(once())
        .with(outBoundP(&st1))
        .will(returnValue(0));

      st_struct_1* p = func3();

      CPPUNIT_ASSERT(p != 0);
      CPPUNIT_ASSERT_EQUAL((long)100, p->field0);
   }

   //
   // a pointer to a struct should be able to
   // outbounded as well.
   //
   void test_func4_should_invoke_service_f0()
   {
      st_struct_0 st1;

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

      MOCKER(service_f0)
        .expects(once())
        .with( outBoundP(&st1)
             , eq(10)
             , eq((float)2.19))
        .will(returnValue((st_struct_1*)0));

      st_struct_0 st2;

      CPPUNIT_ASSERT_EQUAL(0, func4(&st2));
      CPPUNIT_ASSERT_EQUAL(st1.field0, st2.field0);
      CPPUNIT_ASSERT_EQUAL(st1.field1, st2.field1);
      CPPUNIT_ASSERT_EQUAL(0, strcmp(st1.field2, st2.field2));
   }

   //
   // Should be able to outbound any number of objects
   // by specifying the sizeof buffer
   //
   void test_func4_should_invoke_service_f0_with_size()
   {
      st_struct_0 st1[2];

      st1[0].field0 = 101;
      st1[0].field1 = 10.1;
      strcpy(st1[0].field2, "abc");

      st1[1].field0 = 102;
      st1[1].field1 = 10.2;
      strcpy(st1[1].field2, "cba");

      MOCKER(service_f0)
        .expects(once())
        .with( outBoundP(st1, sizeof(st1))
             , eq(10)
             , eq((float)2.19))
        .will(returnValue((st_struct_1*)0));

      st_struct_0 st2[2];

      CPPUNIT_ASSERT_EQUAL(0, func4(st2));

      CPPUNIT_ASSERT_EQUAL(st1[0].field0, st2[0].field0);
      CPPUNIT_ASSERT_EQUAL(st1[0].field1, st2[0].field1);
      CPPUNIT_ASSERT_EQUAL(0, strcmp(st1[0].field2, st2[0].field2));

      CPPUNIT_ASSERT_EQUAL(st1[1].field0, st2[1].field0);
      CPPUNIT_ASSERT_EQUAL(st1[1].field1, st2[1].field1);
      CPPUNIT_ASSERT_EQUAL(0, strcmp(st1[1].field2, st2[1].field2));
   }

   //
   // When trying to outbound a T* object and T is not void, you 
   // can specify another constraint, e,g. eq(), which will be 
   // checked first prior to outbound the pointer.
   //
   void test_func4_should_invoke_service_f0_with_eq()
   {
      st_struct_0 st1;

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

      st_struct_0 st2;

      MOCKER(service_f0)
        .expects(once())
        .with( outBoundP(&st1, eq(&st2))
             , eq(10)
             , eq((float)2.19))
        .will(returnValue((st_struct_1*)0));

      CPPUNIT_ASSERT_EQUAL(0, func4(&st2));
      CPPUNIT_ASSERT_EQUAL(st1.field0, st2.field0);
      CPPUNIT_ASSERT_EQUAL(st1.field1, st2.field1);
      CPPUNIT_ASSERT_EQUAL(0, strcmp(st1.field2, st2.field2));
   }

   //
   // When trying to outbound a void* object, you have to
   // specify the size of outbounded object, otherwise,
   // mockcpp cannot guess the size of buffer by the type.
   //
   void test_func5_should_invoke_service_f6()
   {
      st_struct_0 st1;

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

      MOCKER(service_f6)
        .expects(once())
        .with(outBoundP((void*)&st1, sizeof(st_struct_0)))
        .will(returnValue(1));

      st_struct_0 st2;

      CPPUNIT_ASSERT_EQUAL(1, func5((void*)&st2));
      CPPUNIT_ASSERT_EQUAL(st1.field0, st2.field0);
      CPPUNIT_ASSERT_EQUAL(st1.field1, st2.field1);
      CPPUNIT_ASSERT_EQUAL(0, strcmp(st1.field2, st2.field2));
   }

   //
   // When trying to outbound a void* type pointer, you can 
   // specify another constraint, e,g. eq(), which will be 
   // checked first prior to outbound the pointer.
   //
   void test_func5_should_invoke_service_f6_with_eq()
   {
      st_struct_0 st1;

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

      st_struct_0 st2;

      MOCKER(service_f6)
        .expects(once())
        .with(outBoundP((void*)&st1, sizeof(st_struct_0), eq((void*)&st2)))
        .will(returnValue(1));

      CPPUNIT_ASSERT_EQUAL(1, func5((void*)&st2));
      CPPUNIT_ASSERT_EQUAL(st1.field0, st2.field0);
      CPPUNIT_ASSERT_EQUAL(st1.field1, st2.field1);
      CPPUNIT_ASSERT_EQUAL(0, strcmp(st1.field2, st2.field2));
   }

   //
   // Except for pointer to struct and void, you can outbound
   // char* as well.
   //
   // Note that, char[] cannot be instantiated according to
   // C++ spec, you have to convert it explictly.
   //
   void test_func6_should_invoke_service_f7()
   {
     char* s0 = "abcdefg";
     char  s1[20];

     MOCKER(service_f7)
       .expects(once())
       .with(outBoundP( s0
                      , strlen(s0)+1
                      , eq<char*>(s1))) // has to specify type char*
       .will(returnValue(1));

     
      CPPUNIT_ASSERT_EQUAL(1, func6(s1));
      CPPUNIT_ASSERT_EQUAL(0, strcmp(s0, s1));
   }
   
   //
   // When trying to outbound a pointer to char, if you don't
   // specify the size, you can merely outbound a character (single byte)
   //
   void test_func6_should_invoke_service_f7_as_simple_char()
   {
     char c0 = 'a';
     char c1 = 0;

     MOCKER(service_f7)
       .expects(once())
       .with(outBoundP( &c0
                      , eq<char*>(&c1))) // has to specify type char*
       .will(returnValue(1));

     
      CPPUNIT_ASSERT_EQUAL(1, func6(&c1));
      CPPUNIT_ASSERT_EQUAL('a', c1);
   }


   //
	// When trying to expect 2 const char* or char* are equal,
	// you can use constraint mirror() to compare 2 string 
	// are equal. 
	//
	// Constraint eq(char*) are used to compare the equality
	// the 2 pointers of char type.
	//
	// If your intention is to compare the string, you have to
	// give the length, mockpp merely takes it as a buffer, just
	// like a void* buffer. If the length you want to specify
	// is strlen(s) + 1, you can use contraint smirror(s) instead,
	// which is a facility.
	//
   void test_func6_should_invoke_service_f7_with_mirror()
   {
     char* s0 = "abcdefg";
     char  s1[20];

     memset((void*)s1, 0, 20);

	  strcpy(s1, s0);

     MOCKER(service_f7)
       .expects(once())
       .with(mirror(s1, strlen(s1)+1))
       .will(returnValue(1));

      CPPUNIT_ASSERT_EQUAL(1, func6(s0));
   }

   // 
   // by using smirror, instead of mirror, you don't need to
   // specify the length by yourself anymore. mockcpp will
   // set the length as strlen(s) + 1 automatically.
   //
   void test_func6_should_invoke_service_f7_with_smirror()
   {
     char* s0 = "abcdefg";
     char  s1[20];

     memset((void*)s1, 0, 20);

	  strcpy(s1, s0);

     s1[3] = 'a';

     MOCKER(service_f7)
       .expects(once())
       .with(smirror(s1))
       .will(returnValue(1));

      CPPUNIT_ASSERT_EQUAL(1, func6(s0));
   }

   //
   // When comparing the equality of 2 objects of type char*, if you
   // didn't specify the length, by default, only 1 byte are compared.
   //
   void test_func6_should_invoke_service_f7_with_mirror_for_char()
   {
     char s0 = 'a';
     char s1 = 'a';

     MOCKER(service_f7)
       .expects(once())
       .with(mirror(&s1))
       .will(returnValue(1));

      CPPUNIT_ASSERT_EQUAL(1, func6(&s0));
   }

   // 
   // object pointer version
   //
	void test_func4_should_invoke_service_f0_with_mirror()
   {
      st_struct_0 st1;
      st_struct_0 st2;

		// memset them first to make sure padding bytes are same.
		memset((void*)&st1, 0, sizeof(st1));
      memset((void*)&st2, 0, sizeof(st2));

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

      st2.field0 = 101;
      st2.field1 = 10.1;
      strcpy(st2.field2, "abc");

      MOCKER(service_f0)
        .expects(once())
        .with( mirror(&st1)
             , eq(10)
             , eq((float)2.19))
        .will(returnValue((st_struct_1*)0));

      CPPUNIT_ASSERT_EQUAL(0, func4(&st2));
   }

	//
   // Constraint mirror() can be used to compare if contents
   // of 2 buffers are identical. If the buffer are pointed
   // by void*, you have to specify the length of buffer, 
   // otherwise, a runtime error will be raised.
   //
   void test_func5_should_invoke_service_f6_with_mirror()
   {
		st_struct_0 st0;
      st_struct_0 st1;

		// memset them first to make sure padding bytes are same.
      memset((void*)&st0, 0, sizeof(st0));
      memset((void*)&st1, 0, sizeof(st1));

      st0.field0 = 101;
      st0.field1 = 10.1;
      strcpy(st0.field2, "abc");

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

      MOCKER(service_f6)
        .expects(once())
     // .with(mirror((void*)&st1)) // without specifying the 
                                   // length of buffer, will 
                                   // result in runtime error
        .with(mirror((void*)&st1, sizeof(st1)))
        .will(returnValue(1));

      CPPUNIT_ASSERT_EQUAL(1, func5((void*)&st0));
   }

   //
   // 
   // Constraint mirror() for an object is for comparing the memory
   // map of 2 objects. 
   //
   // It should not be used except that you clearly know what you want.
   //
   // Because, the fields in an object are not always compat,
   // for instance, in an instance of following type,
   //
   // struct Foo {
   //    char a;
   //    int  b;
   // };
   //
   // between field "a" and field "b", there are 3 padding bytes,
   // the value of those byte are random, except that 
   // 1. you cleart hem to zero by using memset or other means, or
   // 2. they are allocated by malloc(...), which will clear the 
   // memory to 0 first before it's returned to user; or
   // 3. they are placed in .bss.
   //
   // Therefore, even if you have set all fields of 2 objects to 
   // exactly same, the memory map of them are like not identical.
   //
   void test_func7_should_invoke_service_f8()
   {
		st_struct_0 st0;
      st_struct_0 st1;

		// memset them first to make sure padding bytes are same.
      memset((void*)&st0, 0, sizeof(st0));
      memset((void*)&st1, 0, sizeof(st1));

      st0.field0 = 101;
      st0.field1 = 10.1;
      strcpy(st0.field2, "abc");

      st1.field0 = 101;
      st1.field1 = 10.1;
      strcpy(st1.field2, "abc");

		MOCKER(service_f8)
        .expects(once())
        .with(mirror(st0))
        .will(returnValue(1));

      CPPUNIT_ASSERT_EQUAL(1, func7(st1));
   }

   
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestService );

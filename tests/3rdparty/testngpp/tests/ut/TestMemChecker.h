#include <testngppst/testngppst.hpp>
#include <mockcpp/mokc.h>

// without this header, can only check memory leak caused by new, and can not specify the allocate file/line.
// with this header included, can check memory leak caused by new or malloc, and can specify the allocate file/line.
// maybe test file do not need this file, but including it in files to be tested is very important, especially for c files.
//#include <mem_checker/interface_4user.h>

#include <vector>
#include <string>
using namespace std;

// mockcpp.lib has been already included in project.
//#pragma comment(lib, "../3rdparty/mockcpp/src/Debug/mockcpp.lib")

struct Dummy 
{
    Dummy(){}
};

#define AVOID_MEM_LEAKS

FIXTURE(TestMemChecker)
{
    TEST(no memory leak in empty test)
    {
    }

	TEST(can detect memory leak caused by new operator)
	{
		unsigned char *p = new unsigned char[10]; // should report memory leak
		
		*p = 0xff;
        *(p+1) = 0xfe;
        *(p+2) = 0x13;
        *(p+3) = 0x21;
        *(p+4) = 0x00;
        *(p+5) = 0x01;
        *(p+6) = 0x08;
		
		#ifdef AVOID_MEM_LEAKS
		delete [] p;
		#endif
	}

    TEST(no memory leaked after delete)
    {
        char *p = new char[55];
        delete [] p;
    }

    TEST(should not report memory leak when using placement new)
    {
        char a[10];
        Dummy *p = new(a) Dummy(); // not report memory leak, only show info message :warning: debug_new used with placement new.
    }

    TEST(can detect memory leak caused by malloc)
    {
        char* p = (char *)malloc(33); // should report memory leak
		
		#ifdef AVOID_MEM_LEAKS
		free(p);
		#endif
    }

    TEST(no memory leaked after free)
    {
        char *p = (char *)malloc(13);
        free(p);
    }

	// @test (memcheck=off)
    TEST(can stop memory checker in a testcase)
    {
        char *p = new char[3]; // should not report memory leak
    }

#if 0
	// after use tags="nomemcheck", this was not supported. ofcourse, if still open STOP/OPEN_MEM_CHECKER api, it works.
    TEST(user can reopen memory checker in a testcase)
    {
        STOP_MEM_CHECKER(); //stopMemChecker();
        char *p = new char[4]; // should not report memory leak
        OPEN_MEM_CHECKER();
        p = new char[5];  // should report memory leak
		
		#ifdef AVOID_MEM_LEAKS
		delete [] p;
		#endif
    }
#endif

    TEST(can report more than one leak)
    {
        char *p1 = new char[4];  // should report memory leak     
        char *p2 = new char[5];  // should report memory leak
		
		#ifdef AVOID_MEM_LEAKS
		delete [] p1;
		delete [] p2;
		#endif
    }

    TEST(support checking memory leak in c file when interface_4user.h included in the c file)
    {
        //char *p = (char*)mallocInCFile(7);   // should report memory leak, i have not found a way to implement this testcase yet, but i test in another project.
    }

    TEST(no memory leak report after free in c file when interface_4user.h included in the c file)
    {
        //char *p = (char*)mallocInCFile(7);   // should not report memory leak, i have not found a way to implement this testcase yet, but i test in another project.
        //freeInCFile(p);
    }

    TEST(user can mock malloc)
    {
#if 0
#undef  malloc
        // TODO: why link error???
        MOCKER(malloc)
            .stubs()
            .will(returnValue(0));
        ASSERT_EQ((void *)0, malloc(123));

        GlobalMockObject::verify(); // TODO: link error! LNK2019: undefined symbol
        GlobalMockObject::reset();

#define malloc(size) debug_malloc(__FILE__, __LINE__, size)
#endif
    }
};


static vector<int> global;

FIXTURE(GlocalVectorMemLeak, global vector)
{
	TEARDOWN()
	{
		global.clear(); // must clear after test. because you should reset all the data changed by test.
	}

	TEST(global vector should not cause report memleak by mistake)
	{
		global.push_back(1);
	}
};

// global or fixture member var are all the same.

FIXTURE(MemberStringMemLeak1, member/global string 1)
{
    string str;
	
	TEST(only assign value to str, not str += something. no need to clear string in teardown) // ofcourse, you can use a str.clear() in teardown, this is a good habit.
	{
	    str = "1";
	}
};

FIXTURE(MemberStringMemLeak2, member/global string 2)
{
    string str;
	
	TEARDOWN()
	{
	    str.clear(); // or: str = "";   (in VC2008, not need this line.)
	}
	
	TEST(there is str += something. need to clear string in teardown)
	{
	    str += "1";
	}
};


FIXTURE(TestMemCheckOffAnnotation)
{
	// @test (memcheck=off)
	TEST(a testcase with memcheck off should not report mem leaks)
	{
		int *p = new int;
	}

    TEST(a testcase without memcheck annotation should report mem leaks)
    {
    	int *p = new int;  // should fail

		#ifdef AVOID_MEM_LEAKS
		delete p;
		#endif
    }
};

//@fixture(memcheck=off)
FIXTURE(TestFixtureMemCheckOffAnnotation)
{
   TEST(fixture has been set to memcheck off, its tests all memcheck off)
   {
       char *p = new char;
   }

   TEST(fixture has been set to memcheck off, its tests all memcheck off 2)
   {
   	   char *p = new char;
   }

   //@test(memcheck=on)
   TEST(fixture has been set to memcheck off, its test can use memcheck on to open mem leak check)
   {
   	   char *p = new char;  // should fail
       #ifdef AVOID_MEM_LEAKS
       delete p;
       #endif   	   
   }
};

//@fixture(memcheck=on)
FIXTURE(TestFixtureMemCheckOnAnnotation)
{
   TEST(fixture has been set to memcheck on, its tests all memcheck on)
   {
       char *p = new char; // should fail
       #ifdef AVOID_MEM_LEAKS
       delete p;
       #endif       
   }

   //@test(memcheck=off)
   TEST(fixture has been set to memcheck on, its test can use memcheck off to close mem leak check)
   {
   	   char *p = new char;
   }
};



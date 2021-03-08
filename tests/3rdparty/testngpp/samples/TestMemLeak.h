
#include <testngpp/testngpp.hpp>

USING_TESTNGPP_NS


FIXTURE(MemLeak)
{
	TEST(new mem leak)
	{
		char *p = new char;
	}
};

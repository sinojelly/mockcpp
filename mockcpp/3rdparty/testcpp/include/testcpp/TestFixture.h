
#ifndef __TESTCPP_FIXTURE_H
#define __TESTCPP_FIXTURE_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestFixture
{
	virtual void setUp() {}
	virtual void tearDown() {}

   virtual ~TestFixture() {}
};

TESTCPP_NS_END

#endif


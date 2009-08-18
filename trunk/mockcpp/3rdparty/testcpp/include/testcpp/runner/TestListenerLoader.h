
#ifndef __TESTCPP_TEST_LISTENER_LOADER_H
#define __TESTCPP_TEST_LISTENER_LOADER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestListener;
struct TestRunnerContext;

struct TestListenerLoader
{
   virtual void load(TestRunnerContext* context) = 0;

	virtual ~TestListenerLoader() {}
};

TESTCPP_NS_END

#endif


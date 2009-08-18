
#ifndef __TESTCPP_TEST_LISTENER_LOADER_H
#define __TESTCPP_TEST_LISTENER_LOADER_H

#include <list>
#include <string>

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestListener;
struct TestRunnerContext;

struct TestListenerLoader
{
   virtual
   void load( TestRunnerContext* context
            , const std::list<std::string>& searchingPaths) = 0;

	virtual ~TestListenerLoader() {}
};

TESTCPP_NS_END

#endif


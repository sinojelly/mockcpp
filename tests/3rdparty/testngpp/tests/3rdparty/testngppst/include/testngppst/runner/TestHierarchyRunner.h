
#ifndef __TESTNGPPST_TEST_HIERARCHY_RUNNER_H
#define __TESTNGPPST_TEST_HIERARCHY_RUNNER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestHierarchyHandler;
struct TestFixtureResultCollector;

struct TestHierarchyRunner
{
	virtual void run 
		( TestHierarchyHandler*
        , TestFixtureResultCollector*) = 0;

   virtual ~TestHierarchyRunner() {}
};

TESTNGPPST_NS_END

#endif


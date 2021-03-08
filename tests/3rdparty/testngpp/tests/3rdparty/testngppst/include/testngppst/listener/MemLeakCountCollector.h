
#ifndef __TESTNGPPST_TEST_CASE_MEM_LEAK_COUNT_COLLECTOR_H
#define __TESTNGPPST_TEST_CASE_MEM_LEAK_COUNT_COLLECTOR_H

#include <testngppst/listener/TestCaseResultCollector.h>

TESTNGPPST_NS_START

struct AssertionFailure;

struct MemLeakCountCollector : public TestCaseResultCollector
{
    MemLeakCountCollector() : memLeakCount(0) {}
	
	void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&)  { memLeakCount++; }

	void endTestCase
		   ( const TestCaseInfoReader*
		   , unsigned int secs
		   , unsigned int uSecs) {}


	int getMemLeakCount() { return memLeakCount; }

private:
	int memLeakCount;
};


struct EmptyCollector : public TestCaseResultCollector
{
    EmptyCollector() {}
	
	void endTestCase
		   ( const TestCaseInfoReader*
		   , unsigned int secs
		   , unsigned int uSecs) {}
};


TESTNGPPST_NS_END

#endif


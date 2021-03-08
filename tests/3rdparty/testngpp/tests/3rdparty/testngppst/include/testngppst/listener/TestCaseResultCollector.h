
#ifndef __TESTNGPPST_TEST_CASE_RESULT_COLLECTOR_H
#define __TESTNGPPST_TEST_CASE_RESULT_COLLECTOR_H

#include <string>

#include <testngppst/testngppst.h>
#include <testngppst/internal/AssertionFailure.h>
#include <testngppst/internal/Warning.h>
#include <testngppst/internal/Info.h>

TESTNGPPST_NS_START

struct AssertionFailure;
struct TestCaseInfoReader;

struct TestCaseResultCollector
{
   virtual void addCaseCrash(const TestCaseInfoReader*) {}
   virtual void addCaseError(const TestCaseInfoReader*, const std::string&) {}
   virtual void addCaseInfo(const TestCaseInfoReader*, const TESTNGPPST_NS::Info&) {}
   virtual void addCaseWarning(const TestCaseInfoReader*, const TESTNGPPST_NS::Warning&) {}
	virtual void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&)  {}
	virtual void addCaseSkipped(const TestCaseInfoReader*)  {}

   virtual void startTestCase
                  ( const TestCaseInfoReader* ) {}

   virtual void endTestCase
                  ( const TestCaseInfoReader*
                  , unsigned int secs
                  , unsigned int uSecs) = 0;

	virtual ~TestCaseResultCollector() {}
};

TESTNGPPST_NS_END

#endif


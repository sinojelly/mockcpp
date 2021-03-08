
#ifndef __TESTNGPPST_TEST_LISTENER_LOADER_H
#define __TESTNGPPST_TEST_LISTENER_LOADER_H

#include <string>

#include <testngppst/testngppst.h>
#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct TestListener;
struct TestResultReporter;
struct TestSuiteResultReporter;
struct TestCaseResultReporter;

struct TestListenerLoader
{
   virtual
   TestListener*
   load( const StringList& searchingPaths
       , const std::string& commandLine
       , TestResultReporter* resultReporter
       , TestSuiteResultReporter* suiteResultReporter
       , TestCaseResultReporter* caseResultReporter) = 0;

	virtual ~TestListenerLoader() {}
};

TESTNGPPST_NS_END

#endif


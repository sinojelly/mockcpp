
#ifndef __TESTNGPPST_TEST_SUITE_LOADER_H
#define __TESTNGPPST_TEST_SUITE_LOADER_H

#include <testngppst/testngppst.h>
#include <testngppst/utils/StringList.h>

TESTNGPPST_NS_START

struct TestSuiteDesc;
struct TestSuiteDescEntryNameGetter;

struct TestSuiteLoader
{
   virtual TestSuiteDesc*
   load( const StringList& searchingPaths
       , const std::string& path
       , TestSuiteDescEntryNameGetter* nameGetter) = 0;

   virtual void unload() = 0;

	virtual ~TestSuiteLoader() {}
};

TESTNGPPST_NS_END

#endif


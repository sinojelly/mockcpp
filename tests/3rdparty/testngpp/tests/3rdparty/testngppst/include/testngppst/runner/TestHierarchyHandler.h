
#ifndef __TESTNGPPST_TEST_HIERARCHY_HANDLER_H
#define __TESTNGPPST_TEST_HIERARCHY_HANDLER_H

#include <utility>

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestFixtureDesc;
struct TestCaseFilter;
struct FixtureTagsFilter;
struct TestFixtureResultCollector;
struct TestCase;
struct TestHierarchyHandlerImpl;

struct TestHierarchyHandler
{
   typedef std::pair<const TestCase*, bool> ValueType;
   
   TestHierarchyHandler
	    ( const std::string& suitePath
	    , TestFixtureDesc* fixture
        , const TestCaseFilter* filter
        , FixtureTagsFilter* tagsFilter
        , TestFixtureResultCollector* collector);

   ~TestHierarchyHandler();

   const std::string& getSuitePath() const;
   void testDone(const TestCase* testcase, bool hasSucceeded);

   unsigned int numberOfTestCasesInSched() const;
 
   ValueType getTestCase(unsigned int index) const;

private:
   TestHierarchyHandlerImpl * This;
};

TESTNGPPST_NS_END

#endif


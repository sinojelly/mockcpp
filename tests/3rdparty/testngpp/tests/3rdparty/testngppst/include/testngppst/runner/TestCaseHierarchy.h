
#ifndef __TESTNGPPST_TESTCASE_HEIRARCHY_H
#define __TESTNGPPST_TESTCASE_HEIRARCHY_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCaseHierarchyImpl;
struct TestFixtureDesc;
struct TestCaseFilter;
struct TestCaseContainer;

struct TestCaseHierarchy
{
public:

   TestCaseHierarchy
         ( const TestFixtureDesc* fixture
         , const TestCaseFilter* filter);

   ~TestCaseHierarchy();

   void
   getDirectSuccessors
         ( const TestCase* testcase
         , TestCaseContainer* container);

   void
   getSuccessors
         ( const TestCase* testcase
         , TestCaseContainer* container);
private:
   TestCaseHierarchyImpl *This;
};

TESTNGPPST_NS_END

#endif


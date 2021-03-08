
#ifndef __TESTNGPPST_SMART_TESTCASE_RESULT_COLLECTOR_H
#define __TESTNGPPST_SMART_TESTCASE_RESULT_COLLECTOR_H

#include <testngppst/listener/TestCaseResultCollector.h>

TESTNGPPST_NS_START

struct SmartTestCaseResultCollector
      : public TestCaseResultCollector
{
   SmartTestCaseResultCollector
         ( TestCaseResultCollector*
         , bool);

   void addCaseCrash(const TestCaseInfoReader*);
   void addCaseError(const TestCaseInfoReader*, const std::string&);
   void addCaseInfo(const TestCaseInfoReader*, const TESTNGPPST_NS::Info&);
   void addCaseWarning(const TestCaseInfoReader*, const TESTNGPPST_NS::Warning&);
   void addCaseFailure(const TestCaseInfoReader*, const AssertionFailure&);
   void addCaseSkipped(const TestCaseInfoReader*);

   void startTestCase(const TestCaseInfoReader*);
   void endTestCase(const TestCaseInfoReader*, unsigned int, unsigned int);

private:
   bool shouldReport() const;
   void startTestCaseIfHaveNot(const TestCaseInfoReader*);

private:
   TestCaseResultCollector* collector;
   bool reportSuccess;
   bool hasFailure;
};

TESTNGPPST_NS_END

#endif


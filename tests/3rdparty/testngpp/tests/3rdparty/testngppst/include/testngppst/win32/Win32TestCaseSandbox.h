
#ifndef __TESTNGPPST_WIN32_TESTCASE_SANDBOX_H
#define __TESTNGPPST_WIN32_TESTCASE_SANDBOX_H

#include <windows.h>
#include <string>

#include <testngppst/testngppst.h>

#include <testngppst/internal/Error.h>

#include <testngppst/runner/SandboxTypedef.h>
#include <testngppst/runner/EOFError.h>

TESTNGPPST_NS_START

struct TestCaseInfoReader;
struct TestCase;
struct TestCaseRunner;
struct TestCaseResultCollector;
struct Win32TestCaseSandboxImpl;

struct Win32TestCaseSandbox
{
   HANDLE getSandboxId() const;
   HANDLE getEventId() const;

   void handle(bool) TESTNGPPST_THROW(Error, EOFError);
   
   const TestCase* getTestCase() const;

   bool hasSucceeded() const;

   bool isDead() const;

   void cleanup();

   ~Win32TestCaseSandbox();

public:

	static Win32TestCaseSandbox*
	createInstance
	     ( const std::string& suiteName
		 , const TestCase* testcase
         , TestCaseRunner* runner
         , TestCaseResultCollector* collector
         , bool shouldReport);

private:
	Win32TestCaseSandbox();

private:
   Win32TestCaseSandboxImpl* This;
};

TESTNGPPST_NS_END

#endif

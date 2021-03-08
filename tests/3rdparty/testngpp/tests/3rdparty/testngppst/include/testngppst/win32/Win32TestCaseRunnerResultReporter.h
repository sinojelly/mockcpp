
#ifndef __TESTNGPPST_TEST_CASE_RUNNER_RESULT_COLLECTOR_H
#define __TESTNGPPST_TEST_CASE_RUNNER_RESULT_COLLECTOR_H

#include <string>
#include <iostream>
#include <windows.h>

#include <testngppst/testngppst.h>

#include <testngppst/listener/TestResultCollector.h>
#include <testngppst/internal/TestSuiteInfoReader.h>
#include <testngppst/internal/TestFixtureInfoReader.h>
#include <testngppst/internal/TestCaseInfoReader.h>

#include <testngppst/internal/AssertionFailure.h>

TESTNGPPST_NS_START

struct TestCaseRunnerResultReporter
	: public TestResultCollector
{

	TestCaseRunnerResultReporter(HANDLE hSemaphore, TestCaseResultCollector* caseReporter)
		: reporter(caseReporter)
		, semaphore(hSemaphore)
	{
	}

	~TestCaseRunnerResultReporter()
	{
		delete reporter;
	}

	void addCaseInfo(const TestCaseInfoReader* testcase, const Info& info)
	{
		reporter->addCaseInfo(testcase, info);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}
	
	void addCaseWarning(const TestCaseInfoReader* testcase, const Warning& warning)
	{
		reporter->addCaseWarning(testcase, warning);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

	void addCaseCrash(const TestCaseInfoReader* testcase)
	{
		reporter->addCaseCrash(testcase);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

	void addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
	{
		reporter->addCaseError(testcase, msg);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

	void addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
	{
		reporter->addCaseFailure(testcase, failure);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

	void addCaseSkipped(const TestCaseInfoReader* testcase)
	{
		reporter->addCaseSkipped(testcase);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

	void startTestCase(const TestCaseInfoReader* testcase)
	{
		reporter->startTestCase(testcase);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

    void endTestCase(const TestCaseInfoReader* testcase, unsigned int secs, unsigned int usecs)
	{
		reporter->endTestCase(testcase, secs, usecs);
		if(semaphore) ::ReleaseSemaphore(semaphore, 1, NULL);
	}

	//////////////////////////////////////////////////////
	void startTestFixture(TestFixtureInfoReader* fixture)
	{
	}
	void endTestFixture(TestFixtureInfoReader* fixture)
	{
	}

	void addFixtureError(TestFixtureInfoReader* fixture, const std::string& error)
	{
	}
	void addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure) 
	{
		std::cerr << "fixuture failure : " << fixture->getName() 
			<< " : " << failure.what() << std::endl;
	}

	void startTestSuite(TestSuiteInfoReader* suite)
	{
	}
	void endTestSuite(TestSuiteInfoReader* suite) 
	{
	}
	void addSuiteError(TestSuiteInfoReader*, const std::string& error)
	{
		std::cerr << "suite error : " << error << std::endl;
	}
	
	void addError(const std::string& error)
	{
		std::cerr << "test error : " << error << std::endl;
	}

private:

    TestCaseResultCollector* reporter;
    HANDLE semaphore;
};

TESTNGPPST_NS_END

#endif


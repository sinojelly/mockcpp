
#include <sstream>
#include <errno.h>

#include <testngpp/AssertionFailure.h>

#include <testngpp/runner/TestCaseSandboxResultReporter.h>

#include <testngpp/comm/WrittableChannel.h>
#include <testngpp/comm/ReadableChannel.h>

TESTNGPP_NS_START

struct TestCaseSandboxResultReporterImpl
{
   TestCaseSandboxResultReporterImpl(WrittableChannel* c)
		: channel(c)
   {}

   ~TestCaseSandboxResultReporterImpl()
   { delete channel; }

	void addCaseError(const TestCaseInfoReader* testCase, const std::string& msg);
	void addCaseFailure(const TestCaseInfoReader* testCase, const AssertionFailure& failure);
	void startTestCase(const TestCaseInfoReader* testCase);
	void endTestCase(const TestCaseInfoReader* testCase);

   WrittableChannel* channel; // Y
};

/////////////////////////////////////////////////////////////////////////
namespace
{
   const unsigned char startCmd = 1;
   const unsigned char endCmd = 2;
   const unsigned char errorCmd = 3;
   const unsigned char failureCmd = 4;
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseError(const TestCaseInfoReader* testCase, const std::string& msg)
{
	channel->writeByte(errorCmd);
   channel->writeString(msg);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseFailure(const TestCaseInfoReader* testCase, const AssertionFailure& failure)
{
	channel->writeByte(failureCmd);
   channel->writeString(failure.getFileName());
   channel->writeInt(failure.getLineOfFile());
   channel->writeString(failure.what());
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
startTestCase(const TestCaseInfoReader* testCase)
{
	channel->writeByte(startCmd);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
endTestCase(const TestCaseInfoReader* testCase)
{
	channel->writeByte(endCmd);
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultReporter::
TestCaseSandboxResultReporter(WrittableChannel* channel)
   : This(new TestCaseSandboxResultReporterImpl(channel))
{
}

/////////////////////////////////////////////////////////////////////////
TestCaseSandboxResultReporter::~TestCaseSandboxResultReporter()
{
   delete This;
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseError(const TestCaseInfoReader* testCase, const std::string& msg)
{
	This->addCaseError(testCase, msg);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseFailure(const TestCaseInfoReader* testCase, const AssertionFailure& failure)
{
	This->addCaseFailure(testCase, failure);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
startTestCase(const TestCaseInfoReader* testCase)
{
	This->startTestCase(testCase);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
endTestCase(const TestCaseInfoReader* testCase)
{
	This->endTestCase(testCase);
}


TESTNGPP_NS_END


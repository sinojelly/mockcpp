
#include <sstream>
#include <errno.h>

#include <testcpp/AssertionFailure.h>

#include <testcpp/runner/TestCaseSandboxResultReporter.h>

#include <testcpp/comm/WrittableChannel.h>
#include <testcpp/comm/ReadableChannel.h>

TESTCPP_NS_START

struct TestCaseSandboxResultReporterImpl
{
   TestCaseSandboxResultReporterImpl(WrittableChannel* c)
		: channel(c)
   {}

   ~TestCaseSandboxResultReporterImpl()
   { delete channel; }

	void addCaseError(TestCaseInfoReader* testCase, const std::string& msg);
	void addCaseFailure(TestCaseInfoReader* testCase, const AssertionFailure& failure);
	void startTestCase(TestCaseInfoReader* testCase);
	void endTestCase(TestCaseInfoReader* testCase);

   WrittableChannel* channel;
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
addCaseError(TestCaseInfoReader* testCase, const std::string& msg)
{
	channel->writeByte(errorCmd);
   channel->writeString(msg);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
addCaseFailure(TestCaseInfoReader* testCase, const AssertionFailure& failure)
{
	channel->writeByte(failureCmd);
   channel->writeString(failure.getFileName());
   channel->writeInt(failure.getLineOfFile());
   channel->writeString(failure.what());
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
startTestCase(TestCaseInfoReader* testCase)
{
	channel->writeByte(startCmd);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporterImpl::
endTestCase(TestCaseInfoReader* testCase)
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
addCaseError(TestCaseInfoReader* testCase, const std::string& msg)
{
	This->addCaseError(testCase, msg);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
addCaseFailure(TestCaseInfoReader* testCase, const AssertionFailure& failure)
{
	This->addCaseFailure(testCase, failure);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
startTestCase(TestCaseInfoReader* testCase)
{
	This->startTestCase(testCase);
}

/////////////////////////////////////////////////////////////////////////
void TestCaseSandboxResultReporter::
endTestCase(TestCaseInfoReader* testCase)
{
	This->endTestCase(testCase);
}


TESTCPP_NS_END


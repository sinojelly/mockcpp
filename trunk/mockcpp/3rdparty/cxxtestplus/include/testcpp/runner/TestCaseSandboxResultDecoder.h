
#ifndef __TESTCPP_TESTCASE_SANDBOX_RESULT_DECODER_H
#define __TESTCPP_TESTCASE_SANDBOX_RESULT_DECODER_H

#include <testcpp/testcpp.h>

TESTCPP_NS_START

struct TestCaseInfoReader;
struct TestCaseResultCollector;
struct ReadableChannel;
struct TestCaseSandboxResultDecoderImpl;

struct TestCaseSandboxResultDecoder
{
   TestCaseSandboxResultDecoder(ReadableChannel*
             , TestCaseInfoReader*
             , TestCaseResultCollector*);

   ~TestCaseSandboxResultDecoder();

	bool decode();

	void flush(bool crashed);

private:

	TestCaseSandboxResultDecoderImpl* This;

};

TESTCPP_NS_END

#endif



#ifndef __TESTNGPPST_TESTCASE_SANDBOX_RESULT_DECODER_H
#define __TESTNGPPST_TESTCASE_SANDBOX_RESULT_DECODER_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

struct TestCaseInfoReader;
struct TestCaseResultCollector;
struct ReadableChannel;
struct TestCaseSandboxResultDecoderImpl;

struct TestCaseSandboxResultDecoder
{
   TestCaseSandboxResultDecoder
         ( ReadableChannel*
         , const TestCaseInfoReader*
         , TestCaseResultCollector*
         , bool);

   ~TestCaseSandboxResultDecoder();

   bool hasError() const;

	bool decode();

	void flush(bool crashed);

private:

	TestCaseSandboxResultDecoderImpl* This;

};

TESTNGPPST_NS_END

#endif


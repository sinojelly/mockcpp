
#ifndef __CPPTEST_READABLE_CHANNEL_H
#define __CPPTEST_READABLE_CHANNEL_H

#include <string>

#include <testcpp/testcpp.h>
#include <testcpp/Error.h>

#include <testcpp/runner/EOFError.h>

TESTCPP_NS_START

struct ReadableChannel
{
   virtual unsigned char readByte() throw (Error, EOFError) = 0;
   virtual int readInt() throw (Error, EOFError) = 0;
   virtual std::string readString() throw (Error, EOFError) = 0;

   virtual void close() = 0;

   virtual ~ReadableChannel() {}
};

TESTCPP_NS_END

#endif


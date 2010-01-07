
#ifndef __CPPTEST_WRITTABLE_CHANNEL_H
#define __CPPTEST_WRITTABLE_CHANNEL_H

#include <string>

#include <testcpp/testcpp.h>
#include <testcpp/Error.h>

TESTCPP_NS_START

struct WrittableChannel
{
   virtual void writeByte(const unsigned char byte) throw (Error) = 0;
   virtual void writeInt(const unsigned int value) throw (Error) = 0;
   virtual void writeString(const std::string& str) throw (Error) = 0;

   virtual void close() = 0;

   virtual ~WrittableChannel() {}
};

TESTCPP_NS_END

#endif


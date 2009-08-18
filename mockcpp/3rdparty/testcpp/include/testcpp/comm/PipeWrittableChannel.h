
#ifndef __CPPTEST_PIPE_WRITTABLE_CHANNEL_H
#define __CPPTEST_PIPE_WRITTABLE_CHANNEL_H

#include <testcpp/testcpp.h>
#include <string>

#include <testcpp/comm/WrittableChannel.h>

TESTCPP_NS_START

struct PipeWrittableChannel
   : public WrittableChannel
{
   PipeWrittableChannel(int channelFd);
   ~PipeWrittableChannel();

   void writeByte(const unsigned char byte) throw (Error);
   void writeInt(const unsigned int value) throw (Error);
   void writeString(const std::string& str) throw (Error);

   void close();

private:
   int fd;
};

TESTCPP_NS_END

#endif


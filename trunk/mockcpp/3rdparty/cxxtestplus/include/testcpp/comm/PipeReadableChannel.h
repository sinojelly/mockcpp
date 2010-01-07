
#ifndef __CPPTEST_PIPE_READABLE_CHANNEL_H
#define __CPPTEST_PIPE_READABLE_CHANNEL_H

#include <testcpp/testcpp.h>

#include <testcpp/comm/ReadableChannel.h>

TESTCPP_NS_START

struct PipeReadableChannel: public ReadableChannel
{
   PipeReadableChannel(int pipeFd);
   ~PipeReadableChannel();

   unsigned char readByte() throw (Error, EOFError); 
   int readInt() throw (Error, EOFError); 
   std::string readString() throw (Error, EOFError); 

   void close();

   int getFD() const;

private:

   int fd;
};

TESTCPP_NS_END

#endif


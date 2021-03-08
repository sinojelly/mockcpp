
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include <testngppst/comm/PipeWrittableChannel.h>

#ifdef __CYGWIN__
typedef _sig_func_ptr sig_t;
#endif

TESTNGPPST_NS_START

//////////////////////////////////////////////////////////
PipeWrittableChannel::PipeWrittableChannel(int channelFd)
   : fd(channelFd)
{
}

//////////////////////////////////////////////////////////
PipeWrittableChannel::~PipeWrittableChannel()
{
   ::close(fd);
}

//////////////////////////////////////////////////////////
static void writeBuf(int fd, const void* buf, size_t size)
{
   int result = 0;

   sig_t originalSigHandler = ::signal(SIGPIPE, SIG_IGN);

   do {
      result = ::write(fd, buf, size);
   } while(result < 0 && errno == EAGAIN);

   ::signal(SIGPIPE, originalSigHandler);

   if(result < 0)
   {
      throw Error(::strerror(errno));
   }
}

//////////////////////////////////////////////////////////
void PipeWrittableChannel::writeByte(const unsigned char byte) TESTNGPPST_THROW(Error)
{
   writeBuf(fd, (const void*)&byte, 1);
}

//////////////////////////////////////////////////////////
void PipeWrittableChannel::writeInt(const unsigned int value) TESTNGPPST_THROW(Error)
{
   writeBuf(fd, (const void*)&value, sizeof(value));
}

//////////////////////////////////////////////////////////
void PipeWrittableChannel::writeString(const std::string& str) TESTNGPPST_THROW(Error)
{
   writeBuf(fd, (const void*)str.c_str(), str.size() + 1);
}

//////////////////////////////////////////////////////////
void PipeWrittableChannel::close()
{
   ::close(fd);
}

//////////////////////////////////////////////////////////

TESTNGPPST_NS_END


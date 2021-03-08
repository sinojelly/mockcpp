
#include <cxxtest/TestSuite.h> 
#include <testngppst/runner/ResourceCheckPoint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <testngpp/comm/PipeReadableChannel.h>

USING_TESTNGPP_NS

class TestPipeReadableChannel: public CxxTest::TestSuite
{
private:

   TESTNGPPST_RCP checkpoint;

   int sockets[2];

public:

   void setUp()
   {
      checkpoint = TESTNGPPST_SET_RESOURCE_CHECK_POINT();

      int result = ::socketpair(AF_UNIX, SOCK_STREAM, 0, sockets);
      TS_ASSERT(result == 0);
   }

   void tearDown()
   {
      ::close(sockets[0]);
      ::close(sockets[1]);

      TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(checkpoint);
   }

   void testShouldBeAbleToReadByte()
   {
      PipeReadableChannel channel(sockets[0]);      

      const char *buf = "abcd";
      int result = ::write(sockets[1], buf, ::strlen(buf));

      TS_ASSERT(result == ::strlen(buf));

      TS_ASSERT_EQUALS((unsigned char)'a', channel.readByte());
      TS_ASSERT_EQUALS((unsigned char)'b', channel.readByte());
      TS_ASSERT_EQUALS((unsigned char)'c', channel.readByte());
      TS_ASSERT_EQUALS((unsigned char)'d', channel.readByte());
   }

   void testShouldThrowEOFErrorAfterReadAllBytesInPipeIfThePipeWasClosedByPeer()
   {
      PipeReadableChannel channel(sockets[0]);      

      const char *buf = "abcd";
      int result = ::write(sockets[1], buf, ::strlen(buf));

      TS_ASSERT(result == ::strlen(buf));
      ::close(sockets[1]);

      TS_ASSERT_EQUALS((unsigned char)'a', channel.readByte());
      TS_ASSERT_EQUALS((unsigned char)'b', channel.readByte());
      TS_ASSERT_EQUALS((unsigned char)'c', channel.readByte());
      TS_ASSERT_EQUALS((unsigned char)'d', channel.readByte());
      TS_ASSERT_THROWS(channel.readByte(), EOFError);
      TS_ASSERT_THROWS(channel.readByte(), EOFError);
   }

   void testShouldThrowErrorIfReadPipeError()
   {
      ::close(sockets[0]);
      PipeReadableChannel channel(sockets[0]);      

      TS_ASSERT_THROWS(channel.readByte(), Error);
   }

   void testShouldBeAbleToReadInt()
   {
      PipeReadableChannel channel(sockets[0]);      

      int value = 1234;
      int result = ::write(sockets[1], &value, sizeof(value));

      TS_ASSERT(result == sizeof(int));

      TS_ASSERT_EQUALS(value, channel.readInt());
   }

   void testShouldBeAbleToReadString()
   {
      PipeReadableChannel channel(sockets[0]);      

      const char *buf = "abcd";
      int result = ::write(sockets[1], buf, ::strlen(buf) + 1);

      TS_ASSERT(result == ::strlen(buf) + 1);

      TS_ASSERT_EQUALS(std::string(buf), channel.readString());
   }

   void testShouldThrowEOFErrorAfterReadAllStuffInPipeIfThePipeWasClosedByPeer()
   {
      PipeReadableChannel channel(sockets[0]);      

      int value = 1234;
      int result = ::write(sockets[1], &value, sizeof(value));
      TS_ASSERT(result == sizeof(value));

      const char *buf = "abcd";
      result = ::write(sockets[1], buf, ::strlen(buf) + 1);
      TS_ASSERT(result == ::strlen(buf) + 1);
      
      ::close(sockets[1]);

      TS_ASSERT_EQUALS(value, channel.readInt());
      TS_ASSERT_EQUALS((unsigned char)'a', channel.readByte());
      TS_ASSERT_EQUALS(std::string("bcd"), channel.readString());

      TS_ASSERT_THROWS(channel.readByte(), EOFError);
      TS_ASSERT_THROWS(channel.readInt(), EOFError);
      TS_ASSERT_THROWS(channel.readString(), EOFError);
   }
};

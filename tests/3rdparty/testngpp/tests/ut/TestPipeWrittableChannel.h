
#include <sys/socket.h>
#include <string.h>

#include <cxxtest/TestSuite.h> 
#include <testngppst/runner/ResourceCheckPoint.h>

#include <testngpp/comm/PipeWrittableChannel.h>

USING_TESTNGPP_NS

class TestPipeWrittableChannel: public CxxTest::TestSuite
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

   void testShouldBeAbleToWriteByte()
   {
      PipeWrittableChannel channel(sockets[0]);

      channel.writeByte('a');
      channel.writeByte('b');
      channel.writeByte('c');

      char buf[4];

      int result = ::read(sockets[1], buf, 3);

      TS_ASSERT(result == 3);

      TS_ASSERT(!::strncmp(buf, "abc", 3));
   }

   void testShouldBeAbleToWriteByteZero()
   {
      PipeWrittableChannel channel(sockets[0]);

      channel.writeByte(0);

      char buf[1];

      int result = ::read(sockets[1], buf, 1);
      TS_ASSERT(result == 1);

      TS_ASSERT(buf[0] == 0);
   }

   void testShouldBeAbleToWriteInt()
   {
      PipeWrittableChannel channel(sockets[0]);

      channel.writeInt(12345);

      int value;

      int result = ::read(sockets[1], &value, sizeof(value));
      TS_ASSERT(result == sizeof(value));

      TS_ASSERT(value == 12345);
   }

   void testShouldBeAbleToWriteIntZero()
   {
      PipeWrittableChannel channel(sockets[0]);

      channel.writeInt(0);

      int value;

      int result = ::read(sockets[1], &value, sizeof(value));
      TS_ASSERT(result == sizeof(int));

      TS_ASSERT(value == 0);
   }

   void testShouldThrowErrorIfWriteIntToBrokenPipe()
   {
      ::close(sockets[0]);
      PipeWrittableChannel channel(sockets[0]);

      TS_ASSERT_THROWS(channel.writeInt(123), Error);
   }

   // Error
   void TtestShouldThrowErrorIfWriteIntToPipeWhichWasClosedByPeer()
   {
      PipeWrittableChannel channel(sockets[0]);

      ::close(sockets[1]);
      
      TS_ASSERT_THROWS(channel.writeInt(123), Error);
   }

   void testShouldBeAbleToWriteString()
   {
      PipeWrittableChannel channel(sockets[0]);

      channel.writeString("abc");

      char buf[4];

      int result = ::read(sockets[1], buf, 4);

      TS_ASSERT(result == 4);

      TS_ASSERT(!::strncmp(buf, "abc", 3));
   }

   void testShouldThrowErrorIfWriteByteToABrokenPipe()
   {
      ::close(sockets[0]);
      PipeWrittableChannel channel(sockets[0]);

      TS_ASSERT_THROWS(channel.writeByte('a'), Error);
   }

   // Error
   void TtestShouldThrowErrorIfWriteByteToPipeWhichWasClosedByPeer()
   {
      PipeWrittableChannel channel(sockets[0]);

      ::close(sockets[1]);
      
      TS_ASSERT_THROWS(channel.writeByte('a'), Error);
   }

   void testShouldThrowErrorIfWriteStringToABrokenPipe()
   {
      ::close(sockets[0]);
      PipeWrittableChannel channel(sockets[0]);

      TS_ASSERT_THROWS(channel.writeString("abc"), Error);
   }

   // Error
   void TtestShouldThrowErrorIfWriteStringToPipeWhichWasClosedByPeer()
   {
      PipeWrittableChannel channel(sockets[0]);

      ::close(sockets[1]);
      
      TS_ASSERT_THROWS(channel.writeString("abc"), Error);
   }

};


#include <sstream>

#include <testngppst/comm/Win32PipeWrittableChannel.h>
#include <testngppst/win32/Win32ThrowLastError.h>

TESTNGPPST_NS_START

//////////////////////////////////////////////////////////
Win32PipeWrittableChannel::Win32PipeWrittableChannel(HANDLE writtableHandle)
   : handle(writtableHandle)
{
}

//////////////////////////////////////////////////////////
Win32PipeWrittableChannel::~Win32PipeWrittableChannel()
{
   close();
}

//////////////////////////////////////////////////////////
static void writeBuf(HANDLE handle, const void* buf, size_t size)
{
   BOOL bSuccess = FALSE;

   DWORD haveWritten = 0;
   bSuccess = WriteFile(handle, buf, size, &haveWritten, NULL);
   if(!bSuccess)
   {
      throwLastError();
   }
}

//////////////////////////////////////////////////////////
void Win32PipeWrittableChannel::writeByte(const unsigned char byte) TESTNGPPST_THROW(Error)
{
   writeBuf(handle, (const void*)&byte, 1);
}

//////////////////////////////////////////////////////////
void Win32PipeWrittableChannel::writeInt(const unsigned int value) TESTNGPPST_THROW(Error)
{
   writeBuf(handle, (const void*)&value, sizeof(value));
}

//////////////////////////////////////////////////////////
void Win32PipeWrittableChannel::writeString(const std::string& str) TESTNGPPST_THROW(Error)
{
   writeBuf(handle, (const void*)str.c_str(), str.size() + 1);
}

//////////////////////////////////////////////////////////
void Win32PipeWrittableChannel::close()
{
   ::CloseHandle(handle);
}

//////////////////////////////////////////////////////////

TESTNGPPST_NS_END


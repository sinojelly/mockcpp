
#if defined(_MSC_VER) || defined(__MINGW32__)
#include <windows.h>

#include <testngppst/internal/Error.h>

TESTNGPPST_NS_START

void throwLastError()
{
    LPVOID lpMsgBuf;

    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

	std::string errorMsg((const char*)lpMsgBuf);
    
	LocalFree(lpMsgBuf);

	throw Error(errorMsg);
}

TESTNGPPST_NS_END

#endif

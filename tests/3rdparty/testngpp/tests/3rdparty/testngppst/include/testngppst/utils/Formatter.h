
#ifndef __TESTNGPPST_FORMATTER_H
#define __TESTNGPPST_FORMATTER_H

#include <testngppst/testngppst.h>

#include <sstream>
#include <string>

#include <testngppst/utils/TypeString.h>

TESTNGPPST_NS_START

///////////////////////////////////////////////////////
std::string toBufferString(void* buf, size_t size);

///////////////////////////////////////////////////////
template <typename T>
std::string toString(T val)
{
   return TESTNGPPST_NS::toBufferString((void*)&val, sizeof(val));
}

///////////////////////////////////////////////////////
std::string toPointerString(void*);

///////////////////////////////////////////////////////
std::string toString(std::string s);
std::string toString(char* s);
std::string toString(const char* s);
std::string toString(float f);
std::string toString(double d);
std::string toString(bool b);
std::string toString(char c);
std::string toString(unsigned char c);
std::string toString(short s);
std::string toString(unsigned short s);
std::string toString(int i);
std::string toString(unsigned int i);
std::string toString(long l);
std::string toString(unsigned long l);

#if (TESTNGPPST_SUPPORT_LONG_LONG == 1)
std::string toString(long long ll);
std::string toString(unsigned long long ll);
#endif

///////////////////////////////////////////////////////
template <typename T>
std::string toString(T* p)
{
   return TESTNGPPST_NS::toPointerString((void*)p);
}

//////////////////////////////////////////
template <typename T>
std::string toValStr(T val)
{
	std::stringstream ss;
	ss << val;
   return ss.str();
}

///////////////////////////////////////////////////////
template <typename T>
std::string toString(const T* s)
{
	return TESTNGPPST_NS::toString(const_cast<T*>(s));
}

/////////////////////////////////////////////////////////////////
template <typename T>
std::string toTypeAndValueString(const T& val)
{
	std::stringstream ss;
	ss << "(" << TESTNGPPST_NS::TypeString<T>::value() << ")"
      << TESTNGPPST_NS::toString(val);
	return ss.str();
}

TESTNGPPST_NS_END

#endif


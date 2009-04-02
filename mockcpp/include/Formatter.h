
#ifndef __MOCKCPP_FORMATTER_H
#define __MOCKCPP_FORMATTER_H

#include <mockcpp.h>

#include <string>
#include <sstream>

#include <OutputStringStream.h>
#include <TypeString.h>

MOCKCPP_NS_START

template <typename T>
std::string toString(T val)
{
	oss_t oss;
	oss << "unknown";
	return oss.str();
}

template <typename T>
std::string toString(T* s)
{
	if(s == 0) return "NULL";

	oss_t oss;

	oss << "0x";
	oss.flags (std::ios::hex);
	oss.fill('0'); oss.width(8);
	oss << reinterpret_cast<int>(s);

	return oss.str();
}

template <typename T>
std::string toString(const T* s)
{
	return toString(const_cast<T*>(s));
}

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

#if (MOCKCPP_SUPPORT_LONG_LONG == 1)
std::string toString(long long ll);
std::string toString(unsigned long long ll);
#endif

/////////////////////////////////////////////////////////////////
template <typename T>
std::string toTypeAndValueString(const T& val)
{
	oss_t oss;
	oss << "(" << TypeString<T>::value() << ")" << toString(val);
	return oss.str();
}

MOCKCPP_NS_END

#endif


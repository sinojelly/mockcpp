/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef __MOCKCPP_FORMATTER_H
#define __MOCKCPP_FORMATTER_H

#include <mockcpp/mockcpp.h>

#include <string>
#include <sstream>

#include <mockcpp/OutputStringStream.h>
#include <mockcpp/TypeString.h>

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
	oss << reinterpret_cast<unsigned long>(s);

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


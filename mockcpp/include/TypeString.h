
#ifndef __MOCKCPP_TYPE_STRING_H
#define __MOCKCPP_TYPE_STRING_H

#include <mockcpp.h>

#include <Void.h>

#include <string>
#include <typeinfo>

MOCKCPP_NS_START

template <typename T> struct TypeString
{
	static std::string value()
	{ return std::string("[") + typeid(T).name() + std::string("]"); }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<std::string>
{
	static std::string value()
	{ return "std::string"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<char*>
{
	static std::string value()
	{ return "char*"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<const char*>
{
	static std::string value()
	{ return "const char*"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<bool>
{
	static std::string value()
	{ return "bool"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<char>
{
	static std::string value()
	{ return "char"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<unsigned char>
{
	static std::string value()
	{ return "uchar"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<wchar_t>
{
	static std::string value()
	{ return "wchar_t"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<short>
{
	static std::string value()
	{ return "short"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<unsigned short>
{
	static std::string value()
	{ return "ushort"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<int>
{
	static std::string value()
	{ return "int"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<unsigned int>
{
	static std::string value()
	{ return "uint"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<long>
{
	static std::string value()
	{ return "long"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<unsigned long>
{
	static std::string value()
	{ return "ulong"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<long long>
{
	static std::string value()
	{ return "int64"; }
};


//////////////////////////////////////////////////////////
template <> struct TypeString<unsigned long long>
{
	static std::string value()
	{ return "uint64"; }
};


//////////////////////////////////////////////////////////
template <> struct TypeString<float>
{
	static std::string value()
	{ return "float"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<double>
{
	static std::string value()
	{ return "double"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<void>
{
	static std::string value()
	{ return "void"; }
};

//////////////////////////////////////////////////////////
template <> struct TypeString<Void>
{
   static std::string value()
   { return "void"; }
};

//////////////////////////////////////////////////////////
template <typename T> struct TypeString<T*>
{
	static std::string value() 
	{ return TypeString<T>::value() + std::string("*"); }
};

//////////////////////////////////////////////////////////
template <typename T> struct TypeString<const T*>
{
	static std::string value() 
	{ return std::string("const ") + TypeString<T>::value() + std::string("*"); }
};

MOCKCPP_NS_END

#endif


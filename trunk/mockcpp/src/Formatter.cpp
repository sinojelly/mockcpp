
#include <mockcpp/OutputStringStream.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

//////////////////////////////////////////
std::string toString(std::string s)
{
	oss_t oss;
	oss << "\"" << s << "\"";
	return oss.str();
}

//////////////////////////////////////////
template <typename T>
std::string toPCharStr(const T& s)
{
	oss_t oss;

	if(s == 0)
      oss << "NULL";
	else
#if 0
	  oss << "\"" << s << "\"";
#endif

    oss << (void*) s;

	return oss.str();
}

//////////////////////////////////////////
std::string toString(char* s)
{ return toPCharStr(s); }

//////////////////////////////////////////
std::string toString(const char* s)
{ return toPCharStr(s); }

//////////////////////////////////////////
std::string toString(bool b)
{
	oss_t oss;
	oss << (b?"true":"false");
	return oss.str();
}

//////////////////////////////////////////
template <typename T>
std::string toHexStr(T val)
{
	oss_t oss;
	oss.flags (std::ios::hex | std::ios::showbase);
	oss << val;
   return oss.str();
}

//////////////////////////////////////////
std::string toHexStr(char val)
{ return toHexStr((int)val&0xFF); }

//////////////////////////////////////////
std::string toHexStr(unsigned char val)
{ return toHexStr((unsigned int)val&0xFF); }

//////////////////////////////////////////
std::string toHexStr(short val)
{ return toHexStr((unsigned int)val&0xFFFF); }

//////////////////////////////////////////
std::string toHexStr(int val)
{ return toHexStr((unsigned int)val&0xFFFFFFFF); }

//////////////////////////////////////////
template <typename T>
std::string toValStr(T val)
{
	oss_t oss;
	oss << val;
   return oss.str();
}

//////////////////////////////////////////
std::string toValStr(char val)
{ return toValStr((int)val); }

//////////////////////////////////////////
std::string toValStr(unsigned char val)
{ return toValStr((unsigned int)val); }

//////////////////////////////////////////
template <typename T>
std::string toHexAndDecStr(T val)
{
	oss_t oss;
	oss << toHexStr(val) << "/" << toValStr(val);
	return oss.str();
}

//////////////////////////////////////////
std::string toString(char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(unsigned char c)
{ return toHexAndDecStr(c); }

//////////////////////////////////////////
std::string toString(short s)
{ return toHexAndDecStr(s); }

//////////////////////////////////////////
std::string toString(unsigned short s)
{ return toHexAndDecStr(s); }

//////////////////////////////////////////
std::string toString(int i)
{ return toHexAndDecStr(i); }

//////////////////////////////////////////
std::string toString(unsigned int i)
{ return toHexAndDecStr(i); }

//////////////////////////////////////////
std::string toString(long l)
{ return toHexAndDecStr(l); }

//////////////////////////////////////////
std::string toString(unsigned long l)
{ return toHexAndDecStr(l); }

//////////////////////////////////////////
std::string toString(long long ll)
{ return toHexAndDecStr(ll); }

//////////////////////////////////////////
std::string toString(unsigned long long ll)
{ return toHexAndDecStr(ll); }

//////////////////////////////////////////
std::string toString(float f)
{ return toValStr(f); }

//////////////////////////////////////////
std::string toString(double f)
{ return toValStr(f); }

//////////////////////////////////////////

MOCKCPP_NS_END


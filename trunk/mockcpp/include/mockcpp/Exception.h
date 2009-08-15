
#ifndef __MOCKCPP_EXCEPTION_H
#define __MOCKCPP_EXCEPTION_H

#include <mockcpp/mockcpp.h>

#include <string>

#if defined(MOCKCPP_USING_CPPUNIT)
#include <cppunit/Exception.h>
#else
#include <exception>
#endif

MOCKCPP_NS_START

#if !defined(MOCKCPP_USING_CPPUNIT)

class Exception
    : public std::exception
{
public:

	Exception (unsigned srcline, const char* srcfile, const std::string &message);

	virtual ~Exception() throw();

   virtual std::string getMessage() const;

	unsigned getSrcLine() const;

	std::string getSrcFile() const;

   virtual const char *what() const throw();

private:

   std::string message;
   unsigned     srcline;
   std::string srcfile;
   mutable std::string  what_helper;
};

#else

class Exception
	: public CPPUNIT_NS::Exception
{
public:
	Exception (unsigned srcline, const char* srcfile, const std::string &msg)
		 : CPPUNIT_NS::Exception( CPPUNIT_NS::Message(msg), CPPUNIT_NS::SourceLine(srcfile, srcline) )
	{}
	
	virtual std::string getMessage() const
	{
		return message().shortDescription();
	}
};

#endif

MOCKCPP_NS_END

#endif


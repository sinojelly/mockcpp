
#ifndef __MOCKCPP_ASSERTION_FAILED_ERROR_H
#define __MOCKCPP_ASSERTION_FAILED_ERROR_H

#include <mockcpp.h>

#include <Exception.h>

MOCKCPP_NS_START

class AssertionFailedError : public Exception
{
  public:

    AssertionFailedError (unsigned srcline, const char* srcfile,
                          const std::string& message);

    virtual ~AssertionFailedError() throw();
};

void
assertionFailed(unsigned srcline
					, const char* srcfile
					, const std::string& message);

MOCKCPP_NS_END

#endif


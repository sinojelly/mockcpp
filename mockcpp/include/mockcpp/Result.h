
#ifndef __MOCKCPP_RESULT_H
#define __MOCKCPP_RESULT_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

class Any;
class SelfDescribe;
class ResultImpl;

struct Result
{
    Result( const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber);

    ~Result();

    Any& getResult(const Any& result) const;

private:

    ResultImpl* This; 
};

MOCKCPP_NS_END

#endif


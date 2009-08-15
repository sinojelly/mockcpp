
#ifndef __MOCKCPP_RESULT_HANDLER_FACTORY_H
#define __MOCKCPP_RESULT_HANDLER_FACTORY_H

#include <mockcpp/mockcpp.h>
#include <string>

MOCKCPP_NS_START

class Any;
class SelfDescribe;
class ResultHandler;
class ResultImpl;

class ResultHandlerFactory
{
public:
    virtual ResultHandler* create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber) = 0;
};

MOCKCPP_NS_END

#endif


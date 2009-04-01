
#ifndef __MOCKCPP_VOID_RESULT_HANDLER_FACTORY_H
#define __MOCKCPP_VOID_RESULT_HANDLER_FACTORY_H

#include <mockcpp.h>
#include <ResultHandlerFactory.h>

MOCKCPP_NS_START

class ResultHandler;

///////////////////////////////////////////////////////////
class VoidResultHandlerFactory
   : public ResultHandlerFactory
{
public:
    ResultHandler* create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber);
};

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif


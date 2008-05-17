
#ifndef __MOCKCPP_MISMATCH_RESULT_HANDLER_FACTORY_H
#define __MOCKCPP_MISMATCH_RESULT_HANDLER_FACTORY_H

#include <mockcpp.h>
#include <ResultHandlerFactory.h>

MOCKCPP_NS_START

///////////////////////////////////////////////////////////
struct MismatchResultHandlerFactory
   : public ResultHandlerFactory
{
    ResultHandler* create(
            const std::type_info& expectedTypeInfo
          , const std::string& expectedTypeString
          , const SelfDescribe* selfDescriber);
};

///////////////////////////////////////////////////////////

MOCKCPP_NS_END

#endif



#ifndef __MOCKCPP_INVOKABLE_H
#define __MOCKCPP_INVOKABLE_H

#include <mockcpp.h>

#include <Any.h>
#include <RefAny.h>

#include <string>

MOCKCPP_NS_START

///////////////////////////////////////////////
class SelfDescribe;

///////////////////////////////////////////////
struct Invokable
{
    virtual Any invoke( const std::string& nameOfCaller
              , const RefAny& p1
              , const RefAny& p2
              , const RefAny& p3
              , const RefAny& p4
              , const RefAny& p5
              , const RefAny& p6
              , const RefAny& p7
              , const RefAny& p8
              , const RefAny& p9
              , const RefAny& p10
              , const RefAny& p11
              , const RefAny& p12
              , SelfDescribe* &resultProvider) = 0;

    virtual ~Invokable() {}
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif


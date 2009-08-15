
#ifndef __MOCKCPP_STRING_PREDICT_H
#define __MOCKCPP_STRING_PREDICT_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/RefAny.h>

MOCKCPP_NS_START

struct StringPredict
{
   virtual bool predict(const std::string& input, const std::string& target) const = 0;
   virtual std::string toString(const std::string& target) const = 0;

   virtual ~StringPredict() {}
};

MOCKCPP_NS_END

#endif



/***
   mockcpp is a C/C++ mock framework.
   Copyright [2008] [Darwin Yuan <darwin.yuan@gmail.com>]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
***/

#ifndef __MOCKCPP_IS_EQUAL_H
#define __MOCKCPP_IS_EQUAL_H

#include <mockcpp/types/AnyCast.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/Formatter.h>
#include <memory>

MOCKCPP_NS_START

template <typename T>
struct IsEqual : public Constraint
{
    IsEqual(const T& expected)
      : expectedValue(expected)
    {}

    ~IsEqual() {}

    bool eval(const RefAny& val) const
    {
      if(!any_castable<T>(val)) return false;
      return any_cast<T>(val) == expectedValue;
    }

    std::string toString() const
    {
      return std::string("eq(") + 
             MOCKCPP_NS::toTypeAndValueString(expectedValue) +
             std::string(")");
    }

private:

    T expectedValue;
};

template <typename V, typename D>
struct IsEqual<std::unique_ptr<V, D> > : public Constraint
{
    IsEqual(const V* expected)
      : expectedValue(expected)
    {}

    ~IsEqual() {}

    bool eval(const RefAny& val) const
    {
        if (val.type() != typeid(std::unique_ptr<V, D>))
        {
            return false;
        }
        return (unique_ptr_any_cast<std::unique_ptr<V, D> >(val)).get() == expectedValue;
    }

    std::string toString() const
    {
      return std::string("eq(unique_ptr ") + 
             MOCKCPP_NS::toTypeAndValueString(expectedValue) +
             std::string(")");
    }

private:

    const V* expectedValue;
};

MOCKCPP_NS_END

#endif


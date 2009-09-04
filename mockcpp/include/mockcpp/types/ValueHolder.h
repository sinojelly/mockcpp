/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef __MOCKPP_VALUEHOLDER_H
#define __MOCKPP_VALUEHOLDER_H

#include <iostream>

#include <mockcpp/mockcpp.h>

#include <mockcpp/types/Holder.h>

#include <mockcpp/EqualityUtil.h>
#include <mockcpp/Formatter.h>

MOCKCPP_NS_START

template<typename ValueType>
class ValueHolder : public Holder<ValueType>
{
public:

    ValueHolder(const ValueType& value)
      : held(value)
    {
    }

    PlaceHolder * clone() const
    { return new ValueHolder(held); }

    const ValueType& getValue() const
    {
      return held;
    }

private:

    ValueType held;
};

///////////////////////////////////////////////
template <typename ValueType>
struct UnsignedLongHolder : public Holder<ValueType>
{
public:

    UnsignedLongHolder(const unsigned long& value)
      : held(value)
    {
    }

    const ValueType& getValue() const
    {
       return reinterpret_cast<const ValueType&>(held);
    }

    PlaceHolder * clone() const
    { return new UnsignedLongHolder(held); }

protected:

    unsigned long held;
};

///////////////////////////////////////////////
template <>
struct ValueHolder<unsigned long> 
   : public UnsignedLongHolder<unsigned long>
{
    ValueHolder(unsigned long value)
      : UnsignedLongHolder<unsigned long>(value)
    {
    }
};

///////////////////////////////////////////////
template <>
struct ValueHolder<unsigned int> 
   : public UnsignedLongHolder<unsigned int>
{
    ValueHolder(unsigned int value)
      : UnsignedLongHolder<unsigned int>(value)
    {
    }
};

///////////////////////////////////////////////
template <>
struct ValueHolder<unsigned short> 
   : public UnsignedLongHolder<unsigned short>
{
    ValueHolder(unsigned short value)
      : UnsignedLongHolder<unsigned short>(value)
    {
    }
};

///////////////////////////////////////////////
template <>
struct ValueHolder<unsigned char> 
   : public UnsignedLongHolder<unsigned char>
{
    ValueHolder(unsigned char value)
      : UnsignedLongHolder<unsigned char>(value)
    {
    }
};

MOCKCPP_NS_END


#endif // __MOCKPP_VALUEHOLDER_H



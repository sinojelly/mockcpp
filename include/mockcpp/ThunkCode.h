/***
    mockcpp is a generic C/C++ mock framework.
    Copyright (C) <2009>  <Darwin Yuan: darwin.yuan@gmail.com>
                                   <Chen Guodong: sinojelly@gmail.com>

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


#ifndef __MOCKCPP_THUNK_CODE_H__
#define __MOCKCPP_THUNK_CODE_H__

#include <mockcpp/mockcpp.h>
#include <mockcpp/ArgumentsMacroHelpers.h>

MOCKCPP_NS_START


struct ThunkCode
{
    virtual const void *thunkCodeStart() const
    {
        return thunkCodeTemplate;
    }
    
    virtual size_t thunkCodeLength() const
    {
        return thunkCodeTemplateSize;
    }

    virtual size_t oldAddrOffset() const = 0;
    virtual size_t newAddrOffset() const = 0;

    virtual ~ThunkCode(){}

protected:
    const void *thunkCodeTemplate;
    size_t thunkCodeTemplateSize;
};

static const size_t MAX_THUNK_CODE_SIZE = 200;


MOCKCPP_NS_END

#endif


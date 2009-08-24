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

#ifndef __MOCKCPP_NORMAL_RESULT_HANDLER_H
#define __MOCKCPP_NORMAL_RESULT_HANDLER_H

#include <mockcpp/mockcpp.h>
#include <mockcpp/ResultHandler.h>

MOCKCPP_NS_START

class Any;

class NormalResultHandler : public ResultHandler
{
public:

    NormalResultHandler(const std::type_info& type);

    bool matches(const Any& result) const;

    const Any& getResult(const Any& result) const;

private:

    const std::type_info& expectedTypeInfo;

};

MOCKCPP_NS_END

#endif


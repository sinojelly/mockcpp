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

#include <mockcpp/InvocationMocker.h>
#include <mockcpp/Constraint.h>
#include <mockcpp/ConstraintSet.h>

MOCKCPP_NS_START

template <typename Builder>
Builder&
ArgumentsMatchBuilder<Builder>::
with( Constraint* c01 
    , Constraint* c02
    , Constraint* c03
    , Constraint* c04
    , Constraint* c05
    , Constraint* c06
    , Constraint* c07
    , Constraint* c08
    , Constraint* c09
    , Constraint* c10
    , Constraint* c11
    , Constraint* c12
)
{
    getMocker()->addMatcher(
      new ConstraintSet(c01, c02, c03, c04, c05, c06,
                        c07, c08, c09, c10, c11, c12));
    return *this;
}


MOCKCPP_NS_END



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

#ifndef __MOCKCPP_DESTRUCTOR_CHECKER_H
#define __MOCKCPP_DESTRUCTOR_CHECKER_H

#include <typeinfo>
#include <algorithm>

#include <mockcpp/mockcpp.h>

MOCKCPP_NS_START

///////////////////////////////////////////////

void* createDestructorChecker(const std::type_info& info);
unsigned int getIndexOfVptrOfDestructor();
unsigned int getIndexOfVtblOfDestructor();

///////////////////////////////////////////////
template <class Interface, class Original>
std::pair<unsigned int, unsigned int> getIndexOfDestructor()
{
   Original* original = (Original*) \
      createDestructorChecker(typeid(Original));

   Interface* checker =  original;

   delete checker;

   unsigned int vptrIndex = 0;
   unsigned int vtblIndex = 0;

   try
   {
      vptrIndex = getIndexOfVptrOfDestructor();
      vtblIndex = getIndexOfVtblOfDestructor();

      // FIXME:
      ::operator delete(original);
   }
   catch(...)
   {
      throw;
   }

   return std::pair<unsigned int, unsigned int>
       (vptrIndex, vtblIndex);
};

///////////////////////////////////////////////

MOCKCPP_NS_END

#endif


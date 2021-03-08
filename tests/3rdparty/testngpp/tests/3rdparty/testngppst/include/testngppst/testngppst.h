/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef __TESTNGPPST_H
#define __TESTNGPPST_H

#if !TESTNGPPST_NO_NAMESPACE
# define TESTNGPPST_NS testngppst
# define TESTNGPPST_NS_START namespace TESTNGPPST_NS {
# define TESTNGPPST_NS_END }
# define USING_TESTNGPPST_NS using namespace TESTNGPPST_NS;
#else
# define TESTNGPPST_NS 
# define TESTNGPPST_NS_START 
# define TESTNGPPST_NS_END 
# define USING_TESTNGPPST_NS 
#endif

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT 
#endif

#ifdef _MSC_VER
#define TESTNGPPST_THROW(...) 
#else
#define TESTNGPPST_THROW(...) throw(__VA_ARGS__)
#endif

#endif

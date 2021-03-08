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

#ifndef __TESTNGPPST_RESOURCE_CHECK_POINT_H
#define __TESTNGPPST_RESOURCE_CHECK_POINT_H

#include <testngppst/testngppst.h>

TESTNGPPST_NS_START

///////////////////////////////////////////////////////////
#if defined(TESTNGPPST_DISABLE_RC) && TESTNGPPST_DISABLE_RC

#define TESTNGPPST_RCP int
#define TESTNGPPST_SET_RESOURCE_CHECK_POINT() 0
#define TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(rcp)
#define TESTNGPPST_VERIFY_RCP_WITH_ERR_MSG(rcp) 

#else

struct ResourceCheckPoint
{
   size_t memory;
   unsigned int fds;
};

#define TESTNGPPST_RCP TESTNGPPST_NS::ResourceCheckPoint
///////////////////////////////////////////////////////////
ResourceCheckPoint testngppstSetCheckPoint();
void testngppstVerifyCheckPoint(const ResourceCheckPoint& rcp
        , const char*, unsigned int);

///////////////////////////////////////////////////////////
#define TESTNGPPST_SET_RESOURCE_CHECK_POINT() \
   TESTNGPPST_NS::testngppstSetCheckPoint()

///////////////////////////////////////////////////////////
#define TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(rcp) do { \
   TESTNGPPST_NS::testngppstVerifyCheckPoint(rcp, __FILE__, __LINE__); \
}while(0)

///////////////////////////////////////////////////////////
#define TESTNGPPST_VERIFY_RCP_WITH_ERR_MSG(rcp) \
  try \
  { \
     TESTNGPPST_VERIFY_RESOURCE_CHECK_POINT(rcp); \
  } \
  catch(std::exception& ex) \
  { \
      std::cerr << __FILE__ << "(" << __LINE__ << "):" \
                  << ex.what() << std::endl; \
  } 

#endif

TESTNGPPST_NS_END

#endif


#ifndef __TESTCPP_RESOURCE_CHECK_POINT_H
#define __TESTCPP_RESOURCE_CHECK_POINT_H

#include <testcpp/testcpp.h>
#include <testcpp/AssertionFailure.h>
#include <testcpp/Error.h>

TESTCPP_NS_START

///////////////////////////////////////////////////////////
struct ResourceCheckPoint
{
   size_t memory;
   unsigned int fds;
};

#define TESTCPP_RCP TESTCPP_NS::ResourceCheckPoint
///////////////////////////////////////////////////////////
ResourceCheckPoint testcppSetCheckPoint();
void testcppVerifyCheckPoint(const ResourceCheckPoint& rcp
        , const char*, unsigned int) throw (Error, AssertionFailure);

///////////////////////////////////////////////////////////
#define TESTCPP_SET_RESOURCE_CHECK_POINT() \
   TESTCPP_NS::testcppSetCheckPoint()

///////////////////////////////////////////////////////////
#define TESTCPP_VERIFY_RESOURCE_CHECK_POINT(rcp) do { \
   TESTCPP_NS::testcppVerifyCheckPoint(rcp, __FILE__, __LINE__); \
}while(0)

///////////////////////////////////////////////////////////

TESTCPP_NS_END

#endif

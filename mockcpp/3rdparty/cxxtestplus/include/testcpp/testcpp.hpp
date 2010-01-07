
#ifndef __TESTCPP_HPP
#define __TESTCPP_HPP

#include <testcpp/testcpp.h>
#include <testcpp/Asserter.h>
#include <testcpp/TestFixture.h>
#include <testcpp/ResourceCheckPoint.h>
#include <testcpp/TestCaseSuccess.h>

#define __BEGIN_TEST     try {
#define __CLEANUP        throw TESTCPP_NS::TestCaseSuccess(); } catch(...) {
#define __END_TEST       throw; }

#endif


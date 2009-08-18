
#ifndef __TESTCPP_H
#define __TESTCPP_H

#if !TESTCPP_NO_NAMESPACE
# define TESTCPP_NS testcpp
# define TESTCPP_NS_START namespace TESTCPP_NS {
# define TESTCPP_NS_END }
# define USING_TESTCPP_NS using namespace TESTCPP_NS;
#else
# define TESTCPP_NS 
# define TESTCPP_NS_START 
# define TESTCPP_NS_END 
# define USING_TESTCPP_NS 
#endif


#endif

